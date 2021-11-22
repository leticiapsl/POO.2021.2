#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

using namespace std;

class Fone{
private:
    string id;
    string number;

public:
    Fone(string id = "", string number = "") : id{id}, number{number}{
    }

    string getId(){
        return this->id;
    }

    string getNumber(){
        return this->number;
    }
    
    static bool validate(string number){ //validade de numero
        int sun = 0;
        for (int i = 0; i < 9; i++){
            sun += number[i] * (10 - 1);
        }
        if (sun % 11 == 0 || sun % 11 == 1){
            if (number[9] == 0){
                return true;
            }else {
                return false;
            }
        }else {
            if (number[9] == (11 - (sun % 11))){
                return true;
            }else {
                return false;
            }
        }
    }

    friend ostream &operator<<(ostream &os, Fone &fone){
        os << fone.id << ": " << fone.number << "]" << endl;
        return os;
    }
};

class Contact{
private:
    string name;
    vector<Fone> fones;

protected:
    string prefix = "-";

private:
    bool foneRepetido(Fone fone){ // aqui ele verifica se há números repetidos
        for (int i = 0; i < (int)this->fones.size(); i++){
            if ((this->fones[i].getId() == fone.getId()) && (this->fones[i].getNumber() == fone.getNumber())){
                return true;
            }
        }
        return false;
    }

public:
    Contact(string name = "") : name{name} {};

    void addFone(Fone fone){
        if (fone.validate != nullptr){ // vai verificar se é diferente de zero, ent vai pro outro if
            if (foneRepetido(fone) == 1){ // aqui vai verifcar se o numero ja existe
                cout << "Numero de telefone ja existente" << endl;
                return; // vai imprimir isso
            }
            this->fones.push_back(fone); // dps de verificar se existe ou nao e continuar, ele vai pegar o fone e adicionar
            cout << "Fone adicionado" << '\n';
        }else {
            cout << "Numero de telefone invalido" << endl; // aq vai rodar caso seja 0 e o numero seja invalido
        }
    }

    void rmFone(int index){
        if (index < 0 || index >= (int)this->fones.size()){
            return;
        }
        this->fones.erase(fones.begin() + index);
        cout << "Fone apagado" << endl;
        return;
    }

    vector<Fone> getFones(){
        return this->fones;
    }

    string getName(){
        return this->name;
    }

    friend std::ostream &operator<<(std::ostream &os, const Contact &cont){
        os << cont.prefix << " ";
        os << cont.name << " ";
        for (int i = 0; i < (int)cont.fones.size(); i++){
            auto fone = cont.fones[i];
            os << "[" << i << ":" << fone << endl;
        }
        return os;
    }
};

class Agenda{
private:
    vector<Contact> contacts;

    int findPos(string name){
        for (int i = 0; i < (int)contacts.size(); i++){
            if (contacts[i].getName() == name){
                return i;
            }
        }
        return -1;
    }

    bool existente(string name){
        for (int i = 0; i < (int)contacts.size(); i++){
            if (contacts[i].getName() == name){
                return true;
            }
        }
        return false;
    }

     bool foneEnc(vector<Fone> fones, string pattern) {
        for(int i = 0; i < (int)fones.size(); i++){
            if (fones[i].getNumber().find(pattern) != string::npos) {
                return true;
            } 
        }
        return false;
    }

public:
    Agenda(){};

    Contact getContact(string name){
        return this->contacts[findPos(name)];
    }

    void addContact(Contact contact){
        if (!existente(contact.getName())){
            this->contacts.push_back(contact);
            return;
        }

        int pos = findPos(contact.getName());
        vector<Fone> fones = contact.getFones();
        for (int i = 0; i < (int)fones.size(); i++){
            contacts[pos].addFone(fones[i]);
        }
    }

    void rmContact(string name){
        int pos = findPos(name);
        if (pos != -1){
            this->contacts.erase(contacts.begin() + pos);
            cout << "Contato selecionado foi apagado" << '\n';
            return;
        }
        cout << "Contato selecionado nao existe na agenda" << '\n';
        return;
    }

    vector<Contact> search(string pattern){
        vector<Contact> contAchados;
        for (int i = 0; i < (int)contacts.size(); i++){// iniciando um ciclo pra buscar um contato pelo nome
            if (contacts[i].getName().find(pattern) != string::npos){
                contAchados.push_back(contacts[i]);
                cout << contAchados[i] << endl;
            }
        }
        for (int i = 0; i < (int)contacts.size(); i++){
            if (foneEnc(contacts[i].getFones(), pattern) == true){
                contAchados.push_back(contacts[i]);
                cout << contAchados[i] << '\n';
            }
        }

         if ((int)contAchados.size() == 0){
            cout << "Nao foi possivel encontrar nada" << endl;
            }
         return contAchados;
    }

    friend std::ostream &operator<<(std::ostream &os, const Agenda &a){
        if ((int)a.contacts.size() == 0){
            os << "Agenda nao possui contatos, esta vazia!! "<< endl;
        }else {
            for (int i = 0; i < (int)a.contacts.size(); i++){
                auto contacts = a.contacts[i];
                os << i << ":";
                os << contacts << endl;
            }
        }
        return os;
    }
};

int main()
{
    cout << "\n" << endl;
    cout << "---AGENDA INICIALIZADA---" << endl;
    Agenda agenda;

    cout << "Adicionando contatos...." << endl;
    Contact Joao{"Joao"};
    Contact Lara{"Lara"};
    Contact Ana{"Ana"};

    Joao.addFone(Fone{"oi", "888"});
    Joao.addFone(Fone{"vivo", "832"});
    Lara.addFone(Fone{"tim", "788"});
    Lara.addFone(Fone{"claro", "138"});
    Ana.addFone(Fone{"vivo", "246"});
    Ana.addFone(Fone{"oi", "23827"});
    Ana.addFone(Fone{"tim", "2234"});

    agenda.addContact(Lara);
    agenda.addContact(Ana);

    cout << agenda << endl;

    cout << "Removendo contatos...." << endl;
    agenda.rmContact("Joao");

    cout << "\n" << endl;
    cout << "Procurando contatos...." << endl;
    agenda.search("7");
    cout << agenda << endl;
}