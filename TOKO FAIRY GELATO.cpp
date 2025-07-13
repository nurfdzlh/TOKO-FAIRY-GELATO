#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

// ===== GELATO CLASS =====
class Gelato {
public:
    string name;
    int price;

    Gelato(string n, int p) {
        name = n;
        price = p;
    }
};

// ===== STORE CLASS =====
class Store {
public:
    vector<Gelato> menu;

    void addMenu(string name, int price) {
        menu.push_back(Gelato(name, price));
    }

    void showMenu() {
        cout << "\n===== MENU GELATO =====\n";
        for (int i = 0; i < menu.size(); ++i) {
            cout << i + 1 << ". " << menu[i].name << " - Rp" << menu[i].price << endl;
        }
    }

    int searchGelato(string target) {
        for (int i = 0; i < menu.size(); ++i) {
            if (menu[i].name == target) return i;
        }
        return -1;
    }

    void sortByPrice() {
        sort(menu.begin(), menu.end(), [](Gelato a, Gelato b) {
            return a.price < b.price;
        });
    }

    void sortByName() {
        sort(menu.begin(), menu.end(), [](Gelato a, Gelato b) {
            return a.name < b.name;
        });
    }
};

// ===== GRAPH CLASS =====
class Graph {
private:
    map<string, vector<string>> adj;

public:
    void addEdge(string a, string b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    void BFS(string start) {
        map<string, bool> visited;
        queue<string> q;
        q.push(start);

        cout << "Cabang yang dikunjungi (BFS): ";
        while (!q.empty()) {
            string current = q.front(); q.pop();
            if (!visited[current]) {
                cout << current << " ";
                visited[current] = true;

                for (auto neighbor : adj[current]) {
                    if (!visited[neighbor]) q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void DFSUtil(string node, map<string, bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        for (auto neighbor : adj[node]) {
            if (!visited[neighbor]) DFSUtil(neighbor, visited);
        }
    }

    void DFS(string start) {
        map<string, bool> visited;
        cout << "Cabang yang dikunjungi (DFS): ";
        DFSUtil(start, visited);
        cout << endl;
    }
};

// ===== MAIN PROGRAM =====
int main() {
    // Tampilkan judul toko
    cout << "===============================\n";
    cout << "        TOKO FAIRY GELATO      \n";
    cout << "  Selamat Datang di Toko Kami  \n";
    cout << "===============================\n";

    Store store;
    store.addMenu("Coklat", 15000);
    store.addMenu("Vanila", 13000);
    store.addMenu("Strawberry", 14000);
    store.addMenu("Matcha", 16000);
    store.addMenu("Mango", 13500);

    Graph cabang;
    cabang.addEdge("Cabang A", "Cabang B");
    cabang.addEdge("Cabang B", "Cabang C");
    cabang.addEdge("Cabang A", "Cabang D");
    cabang.addEdge("Cabang D", "Cabang C");

    int pilihan;
    int total = 0;
    vector<Gelato> keranjang;

    do {
        cout << "\n====== KASIR TOKO GELATO ======\n";
        cout << "1. Tampilkan Menu\n";
        cout << "2. Cari Gelato\n";
        cout << "3. Urutkan Menu (Harga)\n";
        cout << "4. Urutkan Menu (Nama)\n";
        cout << "5. Beli Gelato\n";
        cout << "6. Lihat Total Belanja & Bayar\n";
        cout << "7. Lihat Cabang (BFS)\n";
        cout << "8. Lihat Cabang (DFS)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                store.showMenu();
                break;

            case 2: {
                string cari;
                cout << "Masukkan nama gelato: ";
                getline(cin, cari);
                int idx = store.searchGelato(cari);
                if (idx != -1) {
                    cout << cari << " ditemukan: Rp" << store.menu[idx].price << endl;
                } else {
                    cout << cari << " tidak ditemukan.\n";
                }
                break;
            }

            case 3:
                store.sortByPrice();
                cout << "Menu diurutkan berdasarkan harga.\n";
                break;

            case 4:
                store.sortByName();
                cout << "Menu diurutkan berdasarkan nama.\n";
                break;

            case 5: {
                store.showMenu();
                int beli;
                cout << "Pilih nomor menu yang ingin dibeli: ";
                cin >> beli;
                if (beli >= 1 && beli <= store.menu.size()) {
                    keranjang.push_back(store.menu[beli - 1]);
                    total += store.menu[beli - 1].price;
                    cout << "Berhasil menambahkan " << store.menu[beli - 1].name << " ke keranjang.\n";
                } else {
                    cout << "Menu tidak valid.\n";
                }
                break;
            }

            case 6:
                cout << "\n===== STRUK PEMBELIAN =====\n";
                for (auto& g : keranjang) {
                    cout << g.name << " - Rp" << g.price << endl;
                }
                cout << "Total Belanja: Rp" << total << endl;

                if (total > 0) {
                    int bayar;
                    cout << "Masukkan jumlah uang pembeli: Rp";
                    cin >> bayar;

                    if (bayar >= total) {
                        int kembalian = bayar - total;
                        cout << "Pembayaran berhasil.\n";
                        cout << "Kembalian: Rp" << kembalian << endl;

                        keranjang.clear();
                        total = 0;
                    } else {
                        cout << "Uang tidak cukup. Transaksi dibatalkan.\n";
                    }
                } else {
                    cout << "Belum ada item dalam keranjang.\n";
                }
                break;

            case 7:
                cabang.BFS("Cabang A");
                break;

            case 8:
                cabang.DFS("Cabang A");
                break;

            case 0:
                cout << "Terima kasih telah berbelanja di Toko Fairy Gelato!\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}
