#include <iostream>
#include <iomanip>
#include <limits>
#include "Register.h"
#include "Date.h"
#include "Amount.h"
#include "Transaction.h"


int main() {

    // Inizio, legge il file se esiste
    Register myRegister;
    const std::string filename = "registro_finanziario.csv";
    try {
        myRegister.loadFromFile(filename);
    } catch (const std::exception& e) {
        // Se il file non esiste, mostra un avviso ma non chiudiamo il programma
        std::cout << "[!] Avviso: " << e.what() << ". Sarà creato un nuovo registro al primo salvataggio." << std::endl;
    }

    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- MENU REGISTRO FINANZIARIO ---" << std::endl;
        std::cout << "1. Visualizza tutti i movimenti" << std::endl;
        std::cout << "2. Aggiungi una nuova transazione" << std::endl;
        std::cout << "3. Visualizza il saldo" << std::endl;
        std::cout << "4. Filtra per intervallo delle date" << std::endl;
        std::cout << "0. Salva ed Esci" << std::endl;
        std::cout << "\nScelta: ";
        if (!(std::cin >> choice)) { // Se l'input fallisce
            system("clear");

            std::cout << "\nErrore: Inserisci un numero, non una lettera!" << std::endl;
            std::cin.clear(); // Resetta lo stato di errore
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Premi INVIO per riprovare...";
            std::cin.get();
            system("clear");
            choice = -1;
            continue; // Salta il resto dello switch e torna al menu
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //svuota il buffer del input

        switch (choice) {
            case 1: {
                system("clear");
                std::cout << "\n--- Lista Movimenti ---\n" << std::endl;

                // Verifica se cerano transazioni
                if (myRegister.getTransactions().empty()) {
                    std::cout << "Il registro è vuoto." << std::endl;
                } else {
                    for (const auto& t : myRegister.getTransactions()) {
                        std::string segno = (t.getType() == TransactionType::ENTRATA) ? "[+]" : "[-]";

                        // Stampa le transazioni
                        std::cout << t.getDate().toString() << " " << segno << " "
                                  << t.getDescription() << ": "
                                  << std::fixed << std::setprecision(2) // i numeri avranno 2 numeri decimali
                                  << t.getImport().getValue() << " Euro" << std::endl;
                    }
                }
                std::cout << "\nPremi INVIO per tornare al menu...";
                std::cin.get();

                system("clear");
                break;
            }

            case 2: {
                system("clear");
                int g, m, a;
                double val;
                std::string desc;
                int tipo;

                try {
                    std::cout << "\n--- INSERIMENTO TRANSAZIONE ---\n\n";
                    std::cout << "La data (G/M/A): ";
                    std::cin >> g;
                    std::cin.ignore(1, '/');
                    std::cin >> m;
                    std::cin.ignore(1, '/');
                    std::cin >> a;

                    Date (g, m, a); // controlla se è valida la data

                    std::cout << "L'importo: ";
                    if (!(std::cin >> val)) {
                        // Invece di fare break, lancia un'eccezione
                        throw std::invalid_argument("L'importo deve essere un numero");
                    }

                    std::cout << "Il tipo (1 per ENTRATA, 2 per USCITA): ";
                    if (!(std::cin >> tipo) || (tipo != 1 && tipo != 2)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        throw std::invalid_argument("Il tipo deve essere 1 (Entrata) o 2 (Uscita)");
                    }

                    // Pulizia del buffer fondamentale per la descrizione
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "La descrizione: ";
                    std::getline(std::cin, desc);

                    TransactionType tt = (tipo == 1) ? TransactionType::ENTRATA : TransactionType::USCITA;
                    Transaction nuova(Date(g, m, a), Amount(val), tt, desc);

                    myRegister.addTransaction(nuova);
                    std::cout << "\nLa transazione è stata aggiunta con successo!" << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "\n\nERRORE: " << e.what() << ". Torna al menu e riprova." << std::endl;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                std::cout << "Premi INVIO per tornare al menu...";
                if (std::cin.peek() == '\n') {
                    std::cin.ignore();
                }
                std::cin.get();

                system("clear");
                break;
            }

            case 3: {
                system("clear");
                double saldo = myRegister.computeTotalBalance();
                std::cout << std::fixed << std::setprecision(2); // imposta il saldo con 2 numeri decimali
                std::cout << "\nSALDO TOTALE: " << saldo << " Euro" << std::endl;

                std::cout << "\n\nPremi INVIO per tornare al menu...";
                std::cin.get();

                system("clear");
                break;
            }

            case 4: {
                system("clear");
                int g1, m1, a1;
                int g2, m2, a2;

                std::cout << "\n--- FILTRA PER DATA---\n" << std::endl;

                try {
                    std::cout << "Scrivi la data d' inizio (G/M/A): ";
                    std::cin >> g1;
                    std::cin.ignore(1, '/');
                    std::cin >> m1;
                    std::cin.ignore(1, '/');
                    std::cin >> a1;
                    Date inizio(g1, m1, a1);

                    std::cout << "Scrivi la data di fine (G/M/A): ";
                    std::cin >> g2;
                    std::cin.ignore(1, '/');
                    std::cin >> m2;
                    std::cin.ignore(1, '/');
                    std::cin >> a2;
                    Date fine(g2, m2, a2);

                    if (fine < inizio) {
                        throw std::invalid_argument("La data di fine non può essere precedente alla data d'inizio");
                    }

                    // Chiama la funzione di filtraggio del registro
                    auto filtrate = myRegister.getTransactionsInDateRange(inizio, fine);

                    if (filtrate.empty()) {
                        system("clear");
                        std::cout << "\nRisultati dal filtro, dal " << inizio.toString() << " al " << fine.toString() << ":\n" << std::endl;
                        std::cout << "Nessun movimento trovato in questo periodo." << std::endl;
                    } else {
                        system("clear");
                        std::cout << "\nRisultati dal filtro, dal " << inizio.toString() << " al " << fine.toString() << ":\n" << std::endl;
                        std::cout << std::fixed << std::setprecision(2);
                        for (const auto& t : filtrate) {
                            std::string segno = (t.getType() == TransactionType::ENTRATA) ? "[+]" : "[-]";
                            std::cout << t.getDate().toString() << " " << segno << " "
                            << t.getDescription() << ": " << t.getImport().getValue() << " Euro" << std::endl;
                        }
                        std::cout << "\n\n";
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // pulizia fondamentale
                }catch (const std::exception& e) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cerr << "\n\nERRORE: " << e.what() << ". Torna al menu e riprova." << std::endl;
                }

                std::cout << "Premi INVIO per tornare al menu...";
                std::cin.get();

                system("clear");
                break;
            }

            case 0: {
                // Salva ed Esci
                system("clear");
                std::cout << "\nSalvataggio in corso..." << std::endl;
                myRegister.saveToFile(filename);
                break;
            }

            default: {
                std::cout << "\n\nScelta non valida!" << std::endl;


                std::cout << "Premi INVIO per riprovare...";
                std::cin.clear(); // Pulisce eventuali errori di input
                std::cin.get();

                system("clear");
            }
        }
    }
}