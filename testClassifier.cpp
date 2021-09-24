#include <iostream>
#include "classification/Reader.h"
#include "classification/Classifier.h"
#include "classification/KnnClassifier.h"
#include "sockets/TcpSocket.h"
#include "sockets/TcpServerSocket.h"
#include "io/SocketIO.h"

using std::string;

int main() {

    string msg = "trolololol";
    TcpServerSocket serverSocket(3257, "127.0.0.1");
    TcpSocket client("127.0.0.1", 3257);

    TcpSocket* serverClientSocket = serverSocket.accept();
    SocketIO socketIo(&client);
    socketIo.write(msg);
    cout << serverClientSocket->receive() << endl;


    /*
    string classifiedPath = "../classified.csv";
    string unclassifiedPath = "../unclassified.csv";
    //// initializing the reader for classified and unclassified
    Reader reader(classifiedPath);
    Reader otherReader(unclassifiedPath);
    //// loading the datasets
    vector<Iris*>* classifiedData = reader.buildDataset();
    vector<Iris*>* unclassifiedData = otherReader.buildDataset();
    // applying classifier
    EuclideanDistance calculator;

    Classifiable *c = new Iris(0,0,0,0);

    // creating classifier, classifying all and getting results
    KnnClassifier classifier(5, "EUC", reinterpret_cast<vector<struct Classifiable *> *>(classifiedData),
                             reinterpret_cast<vector<struct Classifiable *> *>(unclassifiedData));

    classifier.classifyAllTestingData();
    vector<string>* ans = classifier.getResults();

    // printing results
    for (const string& s : *ans) {
        std::cout << s << std::endl;
    }
     */
    return 0;
}