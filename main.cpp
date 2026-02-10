#include <iostream>
#include "Register.h"
#include "Date.h"
#include "Amount.h"
#include "Transaction.h"

int main() {

    // Inizio, legge il file se esiste
    Register myRegister;
    std::string filename = "registro_finanziario.csv";

    std::cout << "--- Benvenuto nel tuo Registro Finanziario ---" << std::endl;

    std::cout << "Caricamento dati da " << filename << "..." << std::endl;
    myRegister.loadFromFile(filename);

    // Se il registro è vuoto, gli dà un saldo iniziale
    if (myRegister.getTransactions().empty()) {
        Date dataInizio(1, 2, 2026);
        Amount cifraIniziale(1000.0);
        Transaction deposito(dataInizio, cifraIniziale, TransactionType::ENTRATA, "Saldo Iniziale / Stipendio");
        myRegister.addTransaction(deposito);
        std::cout << "Registro vuoto: aggiunto saldo iniziale di 1000 Euro." << std::endl;
    }
    // Effettua una transazione
    try {
        Date oggi(7, 2, 2026);
        Amount spesa(800.50);
        Transaction t(oggi, spesa, TransactionType::USCITA, "Pranzo fuori");

        myRegister.addTransaction(t);
        std::cout << "Aggiunta transazione: " << t.getDescription() << " (-800.50)" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
    }

    // Mostra la lista delle transazioni
    std::cout << "\nLista Movimenti (Ordinata per data):" << std::endl;
    for (const auto& t : myRegister.getTransactions()) {
        std::string segno = (t.getType() == TransactionType::ENTRATA) ? "[+]" : "[-]";
        std::cout << t.getData().toString() << " " << segno << " "
                  << t.getDescription() << ": " << t.getImport().getValue() << " Euro" << std::endl;
    }

    // Calcola e mostra il saldo
    double saldo = myRegister.computeTotalBalance();
    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "SALDO TOTALE: " << saldo << " Euro" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    // Salva tutto prima di uscire
    std::cout << "Salvataggio in corso..." << std::endl;
    myRegister.saveToFile(filename);

    return 0;
}