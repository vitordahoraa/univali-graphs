
void add_graph_vertice(AdjacencyMatrix &matrix,char is_directed_graph)
{
    int vertices_count = matrix.size();
    vector<int> empty_vertice(vertices_count + 1, 0);
    vector<int> vertice_adjacency_list;

    // include the new vertice in the existent vertices adjacency list
    for(int i = 0; i < vertices_count; i++)
    {
        matrix[i].push_back(0);
    }

    matrix.push_back(empty_vertice);

    vertice_adjacency_list = get_vertice_adjacency_list(vertices_count, vertices_count + 1);
    set_graph_vertice(matrix, vertices_count, vertice_adjacency_list,is_directed_graph);
}

int get_selected_vertice(string message)
{
    int selected_vertice;
    cout << message << endl;
    cout << "~ ";
    cin >> selected_vertice;

    return selected_vertice - 1;
}

void get_new_adjacency(AdjacencyMatrix &matrix)
{
    int vertice = get_selected_vertice("Em qual vertice voce deseja incluir uma aresta/arco?");
    int new_adjacency = get_selected_vertice("Qual vertice sera o novo vertice adjacente?");

    matrix[vertice][new_adjacency] = 1;
}

void remove_graph_vertice(AdjacencyMatrix &matrix, int vertice_to_remove)
{
    if (vertice_to_remove >= matrix.size()) return;

    matrix.erase(matrix.begin() + vertice_to_remove);

    for(int i = 0; i != matrix.size(); i++)
    {
        matrix[i].erase(matrix[i].begin() + vertice_to_remove);
    }
}

void remove_vertice_adjacency(AdjacencyMatrix &matrix)
{
    int vertice = get_selected_vertice("Voce deseja remover uma aresta/arco de qual vertice?");
    int adjacency = get_selected_vertice("Com qual vertice?");

    if (vertice >= matrix.size() || adjacency >= matrix.size()) return;

    matrix[vertice][adjacency] = 0;
}

bool has_unvisited_vertices(vector<bool> vertices)
{
    for(bool visited_vertice : vertices)
        if (!visited_vertice) return true;

    return false;
}

int get_next_unvisited_adjacent_vertice(vector<int> vertice, vector<bool> visited_vertices)
{
    for(int i = 0; i < vertice.size(); i++)
        if(vertice[i] == 1 && !visited_vertices[i]) return i;

    return -1;
}

int get_next_unvisited_vertice(vector<bool> visited_vertices)
{
    for(int i = 0; i < visited_vertices.size(); i++)
        if(!visited_vertices[i]) return i;

    return -1;
}

vector<int> graph_depth_first_search(AdjacencyMatrix matrix, char search_type)
{
    vector<bool> visited_vertices(matrix.size(), false);
    vector<int> visiting_order;
    stack<int> vertices_stack;
    int searched_vertice = -1;

    if(search_type == 'v')
        searched_vertice = get_selected_vertice("Qual vertice voce procura?");

    int root = get_selected_vertice("Qual deve ser o vertice root da busca?");

    while(has_unvisited_vertices(visited_vertices))
    {
        // has no more adjacent vertices
        if (root == -1)
        {
            vertices_stack.pop();
            root = vertices_stack.empty() ? get_next_unvisited_vertice(visited_vertices) : vertices_stack.top();
            root = get_next_unvisited_adjacent_vertice(matrix[root], visited_vertices);
            continue;
        }

        visited_vertices[root] = true;
        visiting_order.push_back(root);
        vertices_stack.push(root);

        if(root == searched_vertice)
        {
            return visiting_order;
        }

        root = get_next_unvisited_adjacent_vertice(matrix[root], visited_vertices);
    }

    cout << "\n\n nao achei essa desgraça \n\n";

    return visiting_order;
}

vector<int> graph_depth_breadth_search(AdjacencyMatrix matrix, char search_type)
{
    vector<bool> visited_vertices(matrix.size(), false);
    vector<int> visiting_order;
    queue<int> vertices_queue;
    int searched_vertice = -1;
    int next_adjacent;

    if(search_type == 'v')
        searched_vertice = get_selected_vertice("Qual vertice voce procura?");

    int root = get_selected_vertice("Qual deve ser o vertice root da busca?");


    visited_vertices[root] = true;
    visiting_order.push_back(root);

    if (root == searched_vertice) return visiting_order;

    while(has_unvisited_vertices(visited_vertices))
    {
        next_adjacent = get_next_unvisited_adjacent_vertice(matrix[root], visited_vertices);

        while (next_adjacent != -1)
        {
            visiting_order.push_back(next_adjacent);

            if (next_adjacent == searched_vertice) return visiting_order;

            visited_vertices[next_adjacent] = true;
            vertices_queue.push(next_adjacent);
            next_adjacent = get_next_unvisited_adjacent_vertice(matrix[root], visited_vertices);
        }

        root = vertices_queue.empty() ? get_next_unvisited_vertice(visited_vertices) : vertices_queue.front();
        vertices_queue.pop();
    }

    return visiting_order;
}

char get_search_type()
{
    char search_type;
    cout << "Digite \"v\" para buscar um vertice especifico ou \"a\" para ver todos os vertices na ordem de visitacao";
    cout << "\n~ ";
    cin >> search_type;

    return search_type;
}
