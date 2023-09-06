

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
