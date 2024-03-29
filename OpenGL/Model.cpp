#include "Model.h"

Model::Model(string filename) {
    maxX = -100000;
    maxY = -100000;
    maxZ = -100000;
    minX = 100000;
    minY = 100000;
    minZ = 100000;
    s = 0.3;
    color = vec3(1, 1, 1);

    load(filename);
    createMesh();
}

Model::~Model() {
    verts.clear();
    tex_coord.clear();
    norms.clear();
    facet_vrt.clear();
    facet_tex.clear();
    facet_nrm.clear();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Model::load(string filename) {
    float sumX = 0;
    float sumY = 0;
    float sumZ = 0;

    ifstream in;
    in.open(filename, ifstream::in);
    if (in.fail()) return;
    string line;

    while (!in.eof()) {
        getline(in, line);
        istringstream iss(line.c_str());
        char trash;

        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            vec3 v;
            for (int i = 0; i < 3; i++) iss >> v[i];
            verts.push_back(v);

            if (v.x > maxX)	maxX = v.x;
            if (v.y > maxY)	maxY = v.y;
            if (v.z > maxZ)	maxZ = v.z;

            if (v.x < minX)	minX = v.x;
            if (v.y < minY)	minY = v.y;
            if (v.z < minZ)	minZ = v.z;

            sumX += v.x;
            sumY += v.y;
            sumZ += v.z;
        }
        else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            vec3 n;
            for (int i = 0; i < 3; i++) iss >> n[i];
            norms.push_back(n);
        }
        else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            vec2 uv;
            for (int i = 0; i < 2; i++) iss >> uv[i];
            tex_coord.push_back({ uv.x, 1 - uv.y });
        }
        else if (!line.compare(0, 2, "f ")) {
            int f, t, n;
            iss >> trash;
            int cnt = 0;
            while (iss >> f >> trash >> t >> trash >> n) {
                facet_vrt.push_back(--f);
                facet_tex.push_back(--t);
                facet_nrm.push_back(--n);
                cnt++;
            }
            if (3 != cnt) {
                cerr << "Error: the obj file is supposed to be triangulated" << endl;
                return;
            }
        }
    }
    in.close();

    avgX = sumX / verts.size();
    avgY = sumY / verts.size();
    avgZ = sumZ / verts.size();

    width = maxX - minX;
    height = maxY - minY;
    depth = maxZ - minZ;
}

void Model::createMesh() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    std::vector<float> meshData;
    for (int i = 0; i < facet_vrt.size(); i++) {
        meshData.push_back(verts[facet_vrt[i]].x);
        meshData.push_back(verts[facet_vrt[i]].y);
        meshData.push_back(verts[facet_vrt[i]].z);

        meshData.push_back(color.x);
        meshData.push_back(color.y);
        meshData.push_back(color.z);
        meshData.push_back(1.0f);

        meshData.push_back(tex_coord[facet_tex[i]].x);
        meshData.push_back(tex_coord[facet_tex[i]].y);

        meshData.push_back(norms[facet_nrm[i]].x);
        meshData.push_back(norms[facet_nrm[i]].y);
        meshData.push_back(norms[facet_nrm[i]].z);
    }

    glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(float), &meshData[0], GL_STATIC_DRAW);

    // Vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7 * sizeof(float)));

    // Normals
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));

    glBindVertexArray(0);
}

void Model::setColor(vec3 color) {
    this->color = color;
}

void Model::draw() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, facet_vrt.size() * 3);
    glBindVertexArray(0);
}

mat4 Model::adjustMatrix() {
    mat4 resize = scale(mat4(1.0f), vec3(s, s, s));
    mat4 origin = translate(mat4(1.0f), vec3(-minX, -minY, -avgZ));

    return resize * origin;
}