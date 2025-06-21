#include <iostream>
#include <string>
#include <vector>
#include <list>
#define nullptr NULL
using namespace std;


struct Ponto {
    double x;
    double y;
};

struct ContornoItem {
    vector<Ponto> pontos;  
    bool ehConvexo;        
};

struct item {
    string nome;
    string nomeDono;
    string propMagica;
    int numIdent;
    int raridade;
    ContornoItem contorno;  
};

struct Aresta
{
    int origem, destino, peso;
};
struct Node
{
    item dado;
    Node *esquerda;
    Node *direita;
};
struct NodeAlfabetica
{
    item dados;
    NodeAlfabetica *esquerda;
    NodeAlfabetica *direita;
};

struct NodeRaridade {
    item dados;
    NodeRaridade *esquerda;
    NodeRaridade *direita;
};

Node *raiz = nullptr;

vector<item> inventario;
list<Aresta> grafo[1000];

bool verificarConvexidade(const vector<Ponto>& pontos) {
    int n = pontos.size();
    if (n < 3) return false;  // Não é polígono válido

    int sinal = 0;
    for (int i = 0; i < n; i++) {
        Ponto p1 = pontos[i];
        Ponto p2 = pontos[(i+1)%n];
        Ponto p3 = pontos[(i+2)%n];

        
        double produtoVetorial = (p2.x - p1.x)*(p3.y - p2.y) - (p2.y - p1.y)*(p3.x - p2.x);

        if (produtoVetorial != 0) {
            if (sinal == 0) {
                sinal = (produtoVetorial > 0) ? 1 : -1;
            } else if ((produtoVetorial > 0 && sinal == -1) || (produtoVetorial < 0 && sinal == 1)) {
                return false;  // Polígono não é convexo
            }
        }
    }
    return true;  // Polígono é convexo
}

NodeAlfabetica *inserirPorNome(NodeAlfabetica *raiz, item novoItem)
{
    if (raiz == NULL)
    {
        NodeAlfabetica *novoNo = new NodeAlfabetica;
        novoNo->dados = novoItem;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        return novoNo;
    }

    if (novoItem.nome < raiz->dados.nome)
        raiz->esquerda = inserirPorNome(raiz->esquerda, novoItem);
    else
        raiz->direita = inserirPorNome(raiz->direita, novoItem);

    return raiz;
}

void listarEmOrdemAlfabetica(NodeAlfabetica *raiz)
{
    if (raiz != NULL)
    {
        listarEmOrdemAlfabetica(raiz->esquerda);
        cout << "Item: " << raiz->dados.nome << endl;
        cout << "Dono: " << raiz->dados.nomeDono << endl;
        cout << "Propriedade: " << raiz->dados.propMagica << endl;
        cout << "Raridade: " << raiz->dados.raridade << endl;
        cout << "-------------------------" << endl;
        listarEmOrdemAlfabetica(raiz->direita);
    }
}

void listar_itens_ordem_alfabetica()
{
    if (inventario.empty())
    {
        cout << "Nenhum item no inventario." << endl;
        return;
    }

    NodeAlfabetica *raiz = NULL;

    // Inserir todos os itens do inventário na árvore
    for (size_t i = 0; i < inventario.size(); i++)
    {
        raiz = inserirPorNome(raiz, inventario[i]);
    }

    cout << "ITENS ORDENADOS POR ORDEM ALFABETICA:" << endl;
    cout << "-------------------------------------" << endl;

    listarEmOrdemAlfabetica(raiz);
}


void visualizar_similaridades()
{
    for (int i = 0; i < 1000; i++)
    {
        if (!grafo[i].empty())
        {
            cout << "Item " << i << " tem similaridades com: ";
            for (list<Aresta>::iterator it = grafo[i].begin(); it != grafo[i].end(); it++)
            {
                cout << "[" << it->destino << " (S=" << it->peso << ")] ";
            }
            cout << endl;
        }
    }
}

void cadastrar_similaridade()
{
    int codigoItem1, codigoItem2, similaridade;
    char continuar;
    char verSimilaridades;
    int tamanhoInventario = inventario.size();

    cout << "CADASTRAR SIMILARIDADE ENTRE ITENS" << endl;
    cout << "---------------------------------" << endl;

    do
    {
        cout << "Digite o codigo do primeiro item: ";
        cin >> codigoItem1;
        cout << "Digite o codigo do segundo item: ";
        cin >> codigoItem2;
        cout << "Digite o valor de similaridade (S) entre eles: ";
        cin >> similaridade;

        bool item1Existe = false, item2Existe = false;
        for (int i = 0; i < tamanhoInventario; i++)
        {
            if (inventario[i].numIdent == codigoItem1)
                item1Existe = true;
            if (inventario[i].numIdent == codigoItem2)
                item2Existe = true;
        }

        if (!item1Existe || !item2Existe)
        {
            cout << "ERRO: Um ou ambos os itens nao existem no inventario!" << endl;
            continue;
        }

        Aresta aresta1;
        aresta1.origem = codigoItem1;
        aresta1.destino = codigoItem2;
        aresta1.peso = similaridade;

        Aresta aresta2;
        aresta2.origem = codigoItem2;
        aresta2.destino = codigoItem1;
        aresta2.peso = similaridade;

        grafo[codigoItem1].push_back(aresta1);
        grafo[codigoItem2].push_back(aresta2);

        cout << "Similaridade cadastrada com sucesso!" << endl;
        cout << "Deseja cadastrar outra similaridade? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');
    cout << endl;
    cout << "Deseja ver a lista de itens similares? (s/n): ";
    cin >> verSimilaridades;
    if (verSimilaridades == 's' || verSimilaridades == 'S')
    {
        cout << endl;
        cout << "LISTA DE SIMILARIDADES" << endl;
        visualizar_similaridades();
    }
}

void inserir_item() {
    item novoItem;
    cout << "VAMOS INSERIR UM NOVO ITEM:" << endl;
    cout << "Insira o nome do item: ";
    cin >> novoItem.nome;
    cout << "Insira o nome do dono: ";
    cin >> novoItem.nomeDono;
    cout << "Insira a propriedade magica: ";
    cin >> novoItem.propMagica;
    cout << "Insira o numero de identificacao: ";
    cin >> novoItem.numIdent;
    cout << "Insira a raridade: ";
    cin >> novoItem.raridade;

    
    int numPontos;
    cout << "Quantos pontos formam o contorno do item? ";
    cin >> numPontos;

    cout << "Digite as coordenadas dos pontos (x y):" << endl;
    for (int i = 0; i < numPontos; i++) {
        Ponto p;
        cout << "Ponto " << i+1 << ": ";
        cin >> p.x >> p.y;
        novoItem.contorno.pontos.push_back(p);
    }

    
    if (!verificarConvexidade(novoItem.contorno.pontos)) {
        cout << "ERRO: O contorno do item nao forma um poligono convexo!" << endl;
        cout << "Item nao pode ser adicionado a bolsa." << endl;
        return;
    }

    
    inventario.push_back(novoItem);
    cout << endl << "ITEM ADICIONADO COM SUCESSO!" << endl << endl;
}

void buscar_items()
{
    int tamanhoInventario = inventario.size();
    string nomeItem, tentarDenovo;
    bool achou = false;
    

    cout << "DIGITE O NOME DO ITEM QUE DESEJA ENCONTRAR: ";
    cin >> nomeItem;
    cout << "-------------------" << endl;
    

    for(int i = 0; i < tamanhoInventario; i++){
        if(inventario[i].nome == nomeItem){
            cout << "ITEM ENCONTRADO" << endl;
            cout << "-------------------" << endl;
            cout << "ITEM: " << inventario[i].nome << endl;
            cout << "PROPRIEDADE: " << inventario[i].propMagica << endl;
            cout << "RARIDADE: " << inventario[i].raridade << endl;
            cout << "-------------------" << endl;
            achou = true;
        }
    }
    if(!achou){
        cout << "NENHUM ITEM ENCONTRADO! DESEJA TENTAR DENOVO? (s/n):";
        cin >> tentarDenovo;
        if(tentarDenovo == "s" || tentarDenovo == "S"){
            buscar_items();
        }
    }
    

    
};

void verificar_item()
{
    string nomeJogador;
    int codigoItemC, valorSimilaridadeX;
    int tamanhoInventario = inventario.size();

    cout << "VERIFICAR ITENS SIMILARES" << endl;
    cout << "------------------------" << endl;
    cout << "Digite o nome do jogador que nao pertence os itens: ";
    cin >> nomeJogador;
    cout << "Digite o codigo do item que vai ser comparado: ";
    cin >> codigoItemC;
    cout << "Digite o valor minimo de similaridade: ";
    cin >> valorSimilaridadeX;

    // Verificar se o item C existe
    bool itemCExiste = false;
    for (int i = 0; i < tamanhoInventario; i++)
    {
        if (inventario[i].numIdent == codigoItemC)
        {
            itemCExiste = true;
            break;
        }
    }

    if (!itemCExiste)
    {
        cout << "ERRO: Item C nao encontrado no inventario!" << endl;
        return;
    }

    cout << endl
         << "ITENS SIMILARES:" << endl;
    cout << "----------------" << endl;

    bool encontrouSimilar = false;

    for (list<Aresta>::iterator it = grafo[codigoItemC].begin(); it != grafo[codigoItemC].end(); it++)
    {
        if (it->peso > valorSimilaridadeX)
        {
            for (int i = 0; i < tamanhoInventario; i++)
            {
                if (inventario[i].numIdent == it->destino && inventario[i].nomeDono != nomeJogador)
                {
                    cout << "Item: " << inventario[i].nome << endl;
                    cout << "Dono: " << inventario[i].nomeDono << endl;
                    cout << "Similaridade: " << it->peso << endl;
                    cout << "----------------" << endl;
                    encontrouSimilar = true;
                    break;
                }
            }
        }
    }

    if (!encontrouSimilar)
    {
        cout << "Nenhum item encontrado com os criterios especificados." << endl;
    }
}

void listar_itens_alfabetica()
{
    listar_itens_ordem_alfabetica();
}

NodeRaridade* inserirPorRaridade(NodeRaridade* raiz, item novoItem) {
    if (raiz == NULL) {
        NodeRaridade* novoNo = new NodeRaridade;
        novoNo->dados = novoItem;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        return novoNo;
    }

    // Decrescente: maiores para a esquerda
    if (novoItem.raridade > raiz->dados.raridade)
        raiz->esquerda = inserirPorRaridade(raiz->esquerda, novoItem);
    else
        raiz->direita = inserirPorRaridade(raiz->direita, novoItem);

    return raiz;
}

void listarEmOrdemRaridade(NodeRaridade* raiz) {
    if (raiz != NULL) {
        listarEmOrdemRaridade(raiz->esquerda);
        cout << "Item: " << raiz->dados.nome << endl;
        cout << "Dono: " << raiz->dados.nomeDono << endl;
        cout << "Propriedade: " << raiz->dados.propMagica << endl;
        cout << "Raridade: " << raiz->dados.raridade << endl;
        cout << "Numero de Identificacao: " << raiz->dados.numIdent << endl;
        cout << "-------------------------" << endl;
        listarEmOrdemRaridade(raiz->direita);
    }
}

void listar_itens_raridade() {
    if (inventario.empty()) {
        cout << "Nenhum item no inventario." << endl;
        return;
    }

    NodeRaridade* raiz = NULL;

    // Inserir todos os itens na árvore por raridade
    for (size_t i = 0; i < inventario.size(); i++) {
        raiz = inserirPorRaridade(raiz, inventario[i]);
    }

    cout << "ITENS ORDENADOS POR RARIDADE (DECRESCENTE):" << endl;
    cout << "------------------------------------------" << endl;

    listarEmOrdemRaridade(raiz);
}



void contar_itens_mesma_prop()
{
    int tamanhoInventario = inventario.size();
    string propTarget;
    int contador = 0;

    cout << "QUAL PROPRIEDADE DESEJA CONTAR: ";
    cin >> propTarget;
    cout << "-----------------" << endl;

    for(int i = 0; i < tamanhoInventario; i++){
        if(inventario[i].propMagica == propTarget){
            contador ++;
        }
    }

    cout << "EXISTEM " << contador << " ITENS COM ESSA PROPRIEDADE!" << endl;

}

void remover_itens_menos_raros()
{
    if (inventario.empty())
    {
        cout << "Nenhum item no inventario." << endl;
        return;
    }

    int raridadeMinima;
    cout << "Digite o valor minimo de raridade (R): ";
    cin >> raridadeMinima;

    vector<int> itensRemovidos;

   
    for (vector<item>::iterator it = inventario.begin(); it != inventario.end(); )
    {
        if (it->raridade < raridadeMinima)
        {
            itensRemovidos.push_back(it->numIdent);
            it = inventario.erase(it);
        }
        else
        {
            ++it;
        }
    }

   
    for (size_t i = 0; i < itensRemovidos.size(); ++i)
    {
        int id = itensRemovidos[i];
        grafo[id].clear();
    }

   
    for (size_t i = 0; i < 1000; ++i)
    {
        for (list<Aresta>::iterator it = grafo[i].begin(); it != grafo[i].end(); )
        {
            bool destinoFoiRemovido = false;
            for (size_t j = 0; j < itensRemovidos.size(); ++j)
            {
                if (it->destino == itensRemovidos[j])
                {
                    destinoFoiRemovido = true;
                    break;
                }
            }

            if (destinoFoiRemovido)
            {
                it = grafo[i].erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    cout << "Itens com raridade menor que " << raridadeMinima << " foram removidos." << endl;
    cout << "Total de itens removidos: " << itensRemovidos.size() << endl;
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
        cout << "3 - buscar itens" << endl;
        cout << "4 - verificar itens" << endl;
        cout << "5 - listar itens por ordem alfabetica" << endl;
        cout << "6 - listar itens por raridade" << endl;
        cout << "7 - contar items com a mesma propriedade" << endl;
        cout << "8 - remover itens menos raros" << endl;
        cout << "9 - sair do inventario" << endl;
        cout << "" << endl;
        cout << "Digite uma opcao: ";
        cin >> opcao;
        cout << "----------------------------" << endl;
        switch (opcao)
        {
        case 1:
            inserir_item();
            break;
        case 2:
            cadastrar_similaridade();
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
        case 9:
            cout << endl;
            cout << "OBRIGADO POR UTILIZAR O INVENTARIO, ATE A PROXIMA! :)" << endl;
            cout << endl;
            return 0;
            break;
        default:
            break;
        }
        cout << "----------------------------" << endl;
    }

    return 0;
}
