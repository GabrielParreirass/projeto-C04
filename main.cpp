#include <iostream>
using namespace std;

void inserir_item()
{
    cout << "Funcionalidade em construcao" << endl;
};

void cadastrar_similidaridade()
{
    cout << "Funcionalidade em construcao" << endl;
};

void buscar_items()
{
    cout << "Funcionalidade em construcao" << endl;
};

void verificar_item()
{
    cout << "Funcionalidade em construcao" << endl;
};

void listar_itens_alfabetica()
{
    cout << "Funcionalidade em construcao" << endl;
};

void listar_itens_raridade()
{
    cout << "Funcionalidade em construcao" << endl;
};

void contar_itens_mesma_prop()
{
    cout << "Funcionalidade em construcao" << endl;
}

void remover_itens_menos_raros()
{
    cout << "Funcionalidade em construcao" << endl;
}

int main()
{

    int opcao;

    while (true)
    {
        cout << "" << endl;
        cout << "Escolha uma opcao abaixo: " << endl;
        cout << "1 - inserir item" << endl;
        cout << "2 - cadastrar similaridade" << endl;
        cout << "3 - bucar itens" << endl;
        cout << "4 - verificar itens" << endl;
        cout << "5 - listar itens por ordem alfabetica" << endl;
        cout << "6 - listar itens por raridade" << endl;
        cout << "7 - contar items com a mesma propriedade" << endl;
        cout << "8 - remover itens menos raros" << endl;
        cout << "" << endl;
        cout << "Digite uma opcao: ";
        cin >> opcao;
        switch (opcao)
        {
        case 1:
            inserir_item();
            break;
        case 2:
            cadastrar_similidaridade();
            break;
        case 3:
            buscar_items();
            break;
        case 4:
            verificar_item();
            break;
        case 5:
            listar_itens_alfabetica();
            break;
        case 6:
            listar_itens_raridade();
            break;
        case 7:
            contar_itens_mesma_prop();
            break;
        case 8:
            remover_itens_menos_raros();
            break;
        default:
            break;
        }
    }

    return 0;
}