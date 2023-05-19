#define _CRT_SECURE_NO_WARNINGS
#include "Text2D.h"

Text2D::Text2D(const char* texturePath) {
	Text2DTextureID = loadDDS(texturePath);

	glGenBuffers(1, &Text2DVertexBufferID);
	glGenBuffers(1, &Text2DUVBufferID);

	textShader = new Shader("text.vert", "text.frag");
	Text2DShaderID = textShader->program;
	Text2DUniformID = glGetUniformLocation(Text2DShaderID, "texture_sample");
}

void Text2D::printText2D(const char * text, int x, int y, int size) {
	unsigned int length = strlen(text);

	vector<vec2> vertices;
	vector<vec2> UVs;

	for ( unsigned int i=0 ; i<length ; i++ ){
		vec2 vertex_up_left    = vec2( x+i*size     , y+size );
		vec2 vertex_up_right   = vec2( x+i*size+size, y+size );
		vec2 vertex_down_right = vec2( x+i*size+size, y      );
		vec2 vertex_down_left  = vec2( x+i*size     , y      );

		vertices.push_back(vertex_up_left   );
		vertices.push_back(vertex_down_left );
		vertices.push_back(vertex_up_right  );

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = text[i];
		float uv_x = (character%16)/16.0f;
		float uv_y = (character/16)/16.0f;

		vec2 uv_up_left    = vec2( uv_x             , uv_y );
		vec2 uv_up_right   = vec2( uv_x + 1.0f/16.0f, uv_y );
		vec2 uv_down_right = vec2( uv_x + 1.0f/16.0f, (uv_y + 1.0f/16.0f) );
		vec2 uv_down_left  = vec2( uv_x             , (uv_y + 1.0f/16.0f) );
		UVs.push_back(uv_up_left);
		UVs.push_back(uv_down_left);
		UVs.push_back(uv_up_right);

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}

	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(vec2), &UVs[0], GL_STATIC_DRAW);

	glUseProgram(Text2DShaderID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
	glUniform1i(Text2DUniformID, 0);

	// vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	// texCoord (UVs)
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Text2D::cleanupText2D() {
	glDeleteBuffers(1, &Text2DVertexBufferID);
	glDeleteBuffers(1, &Text2DUVBufferID);
	glDeleteTextures(1, &Text2DTextureID);
	glDeleteProgram(Text2DShaderID);
}


GLuint Text2D::loadDDS(const char * imagepath) {
	unsigned char header[124];
	FILE *fp; 
 
	fp = fopen(imagepath, "rb"); 
	if (fp == NULL) {
		printf("%s could not be opened.\n", imagepath); getchar(); 
		return 0;
	}
   
	char filecode[4]; 
	fread(filecode, 1, 4, fp); 
	if (strncmp(filecode, "DDS ", 4) != 0) { 
		fclose(fp); 
		return 0; 
	}
	
	fread(&header, 124, 1, fp); 

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);
 
	unsigned char * buffer;
	unsigned int bufsize;

	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
	fread(buffer, 1, bufsize, fp); 
	fclose(fp);

	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4; 
	unsigned int format;

	switch(fourCC) { 
	case FOURCC_DXT1: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
		break; 
	case FOURCC_DXT3: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
		break; 
	case FOURCC_DXT5: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
		break; 
	default: 
		free(buffer); 
		return 0; 
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
	
	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
	unsigned int offset = 0;

	// load the mipmaps
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) { 
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset); 
	 
		offset += size; 
		width  /= 2; 
		height /= 2; 

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if(width < 1) width = 1;
		if(height < 1) height = 1;
	} 

	free(buffer); 
	return textureID;
}