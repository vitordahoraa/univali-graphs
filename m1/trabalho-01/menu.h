
void print_main_menu()
{
    cout << "Escolha uma opção:";
    cout << "\n[ a ] Incluir vertice";
    cout << "\n[ b ] Incluir aresta/arco";
    cout << "\n[ c ] Remover vertice";
    cout << "\n[ d ] Remover aresta/arco";

    cout << "\n\n[ l ] Realizar busca por largura";
    cout << "\n[ p ] Realizar busca por profundidade";

    cout << "\n\n[ q ] Sair";
}

bool validate_selected_menu_option(char option)
{
    return
        option == 'a'
        || option == 'b'
        || option == 'c'
        || option == 'd'

        || option == 'l'
        || option == 'p'

        || option == 'q';
}

char get_valid_menu_option()
{
    char selected_option;
    bool is_valid_option;

    do
    {
        cout << "\n~ ";
        cin >> selected_option;

        selected_option = tolower(selected_option);

        is_valid_option = validate_selected_menu_option(selected_option);
        if(!is_valid_option) cout << "[!] Opcao invalida\n\n";
    }
    while (!is_valid_option);

    return selected_option;
}