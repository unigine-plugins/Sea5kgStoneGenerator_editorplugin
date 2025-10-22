/*
MIT License

Copyright (c) 2022-2025 mrseakg@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Repository: https://github.com/unigine-plugins/Sea5kgStoneGenerator_editorplugin
*/


    // How to copy mesh by code
    Unigine::MeshPtr mesh = Unigine::Mesh::create("sphere_0.mesh");

    std::cout << std::endl << "mesh->getNumIndices() = " << mesh->getNumIndices(0) << std::endl;
    std::cout << std::endl << "mesh->getNumVertex() = " << mesh->getNumVertex(0) << std::endl;
    std::cout << std::endl << "mesh->getNumCIndices() = " << mesh->getNumCIndices(0) << std::endl;
    std::cout << std::endl << "mesh->getNumCVertex() = " << mesh->getNumCVertex(0) << std::endl;
    std::cout << std::endl << "mesh->getNumTangents() = " << mesh->getNumTangents(0) << std::endl;
    std::cout << std::endl << "mesh->getNumTIndices() = " << mesh->getNumTIndices(0) << std::endl;
    std::cout << std::endl << "mesh->getNumTVertex() = " << mesh->getNumTVertex(0) << std::endl;
    std::cout << std::endl << "mesh->getNumWeights() = " << mesh->getNumWeights(0) << std::endl;
    std::cout << std::endl << "mesh->getNumNormals() = " << mesh->getNumNormals(0) << std::endl;


    // mesh->getNumVertex() = 994
    // mesh->getNumCVertex() = 994

    // mesh->getNumIndices() = 5952
    // mesh->getNumTIndices() = 5952
    // mesh->getNumCIndices() = 5952

    // mesh->getNumTangents() = 1357
    // mesh->getNumTVertex() = 1357

    // make the table of tangents
    Unigine::MeshPtr mesh = Unigine::Mesh::create("sphere_0.mesh");
    m_pMeshTemp = Unigine::Mesh::create();
    nSurface = m_pMeshTemp->addSurface("0");
    std::cout << std::endl;
    int tvertexes = mesh->getNumTIndices(0); // 5952
    for (int i = 0; i < tvertexes; i++) {
        int nCIndex = mesh->getCIndex(i, 0); // 5952 -> 994
        Unigine::Math::vec3 v = mesh->getVertex(nCIndex, 0);

        int tindex = mesh->getTIndex(i, 0); // 5952 -> 1357
        Unigine::Math::quat t = mesh->getTangent(tindex, 0);
        m_pMeshTemp->addVertex(v, nSurface);
        m_pMeshTemp->addTangent(t, nSurface);
        m_pMeshTemp->addIndex(i, nSurface);
    }
