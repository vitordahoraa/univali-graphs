#include <limits>

typedef vector<vector<int>> AdjacencyMatrix;

bool is_adjacent_vertices(AdjacencyMatrix matrix, int i, int j)
{
    return matrix[i][j] == 1;
}

void print_adjacent_matrix_row(AdjacencyMatrix matrix, int i)
{
    printf("[ %d ] => ", i + 1);
    for(int j = 0; j < matrix.size(); j++)
    {
        if(is_adjacent_vertices(matrix, i, j))
            printf("%d\t", j + 1);
    }
}


void print_adjacent_matrix(AdjacencyMatrix matrix)
{
    for(int i = 0; i < matrix.size(); i++)
    {
        print_adjacent_matrix_row(matrix, i);
        printf("\n");
    }
}

void set_graph_vertice(AdjacencyMatrix &matrix, int vertice, vector<int> adjacency_list,char is_directed_graph)
{
    for(int i = 0; i < adjacency_list.size(); i++){
        matrix[vertice][adjacency_list[i] - 1] = 1;
        if(is_directed_graph == false) matrix[adjacency_list[i] - 1][vertice] = 1;
    }

}

vector<int> get_vertice_adjacency_list(int vertice, int vertices_count)
{
    string adjacent_vertices;
    string adjacent_vertice_as_string;
    int adjacent_vertice;

    vector<int> adjacency_list;

    // BUG: the adjacency list needs to begin with a whitespace
    printf("Digite os vertices adjacentes ao vertice %d, separados por espacos (ex: 2 5 9)\n", vertice + 1);
    printf("~");
    std::getline(std::cin, adjacent_vertices);

    // adjacent_vertices is a string with the pattern "1 2 3", where each number represents one adjacent vertice of i
    std::istringstream iss(adjacent_vertices);

    while(iss >> adjacent_vertice_as_string)
    {
        adjacent_vertice = stoi(adjacent_vertice_as_string);

        if (adjacent_vertice > vertices_count) continue;
        adjacency_list.push_back(adjacent_vertice);
    }
    return adjacency_list;
}

void get_graph_initial_state(AdjacencyMatrix &matrix, char is_directed_graph)
{
    string adjacent_vertices;
    string vertice;

    vector<int> vertice_adjacency_list;
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

    for(int i = 0; i < matrix.size(); i++)
    {
        vertice_adjacency_list = get_vertice_adjacency_list(i, matrix.size());

        set_graph_vertice(matrix, i, vertice_adjacency_list, is_directed_graph);
    }
}


string get_graph_type()
{
    char user_answer;

    cout << "O grafo é direcionado (y/n)? ";
    cin >> user_answer;

    user_answer = tolower(user_answer);

    return user_answer == 'y' ? "directed" : "non-directed";
}

int get_vertices_count()
{
    int vertices;

    cout << "O grafo tem quantos vertices? ";
    cin >> vertices;

    return vertices;
}

bool is_matrix_empty(int** matrix, int rows)
{
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
            if(matrix[i][j] == 1) return false;

    return true;
}
