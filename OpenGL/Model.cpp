#include "Model.h"

Model::Model(string filename) {
    load(filename);
}

void Model::load(string filename) {
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
        }
        else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            vec3 n;
            for (int i = 0; i < 3; i++) iss >> n[i];
            norms.push_back(normalize(n));
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
}

void Model::draw() {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < facet_vrt.size(); i++) {
        glNormal3f(norms[facet_nrm[i]].x, norms[facet_nrm[i]].y, norms[facet_nrm[i]].z);
        glTexCoord2f(tex_coord[facet_tex[i]].x, tex_coord[facet_tex[i]].y);
        glVertex3f(verts[facet_vrt[i]].x, verts[facet_vrt[i]].y, verts[facet_vrt[i]].z);
    }
    glEnd();
}
