#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ---------------------------------------------------------
// Hàm KSA: Key-Scheduling Algorithm
// ---------------------------------------------------------
void KSA(vector<int>& S, const vector<int>& K) {
    int N = 256;
    
    // Khởi tạo S = [0, 1, ..., 255]
    for (int i = 0; i < N; i++) {
        S.push_back(i);
    }
    
    // Xáo trộn S
    int j = 0;
    for (int i = 0; i < N; i++) {
        j = (j + S[i] + K[i % K.size()]) % N;
        swap(S[i], S[j]);
    }
}

// ---------------------------------------------------------
// Hàm PRGA: Pseudo-Random Generation Algorithm
// ---------------------------------------------------------
void PRGA(vector<int>& S, const string& plaintext, vector<int>& keystream, vector<int>& ciphertext) {
    int N = 256;
    int i = 0, j = 0;
    
    for (size_t k = 0; k < plaintext.length(); k++) {
        // Cập nhật trạng thái
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(S[i], S[j]);
        
        // Lấy giá trị dòng khóa t
        int t = (S[i] + S[j]) % N;
        int k_stream = S[t];
        keystream.push_back(k_stream);
        
        // XOR tạo bản mã
        int m_ascii = (int)plaintext[k];
        ciphertext.push_back(m_ascii ^ k_stream);
    }
}

// ---------------------------------------------------------
// Hàm MAIN: Chạy test case
// ---------------------------------------------------------
int main() {
    // 1. Dữ liệu test case
    vector<int> K = {2, 4, 1, 7};
    string m = "cybersecurity";
    
    vector<int> S;          // Vector trạng thái
    vector<int> key_stream; // Lưu dòng khóa
    vector<int> ciphertext; // Lưu bản mã
    
    cout << "--- TEST CASE THUAT TOAN RC4 (N = 256) ---" << endl;
    cout << "Ban ro (m) = " << m << endl;
    cout << "Khoa (K) = [2, 4, 1, 7]" << endl;
    
    // 2. Gọi hàm thực thi thuật toán
    KSA(S, K);
    PRGA(S, m, key_stream, ciphertext);
    
    // 3. In kết quả test (Chỉ in tối đa 10 giá trị đầu)
    int print_limit = min(10, (int)m.length());
    cout << "\n=> IN RA " << print_limit << " GIA TRI DAU TIEN DE TEST:\n" << endl;
    
    cout << "1. DONG KHOA DUOC TAO RA (Keystream):" << endl;
    for (int k = 0; k < print_limit; k++) {
        cout << key_stream[k] << " ";
    }
    cout << "\n\n";

    cout << "2. BAN MA (Ciphertext):" << endl;
    cout << left << setw(10) << "Ky tu" 
         << setw(10) << "ASCII" 
         << setw(15) << "Keystream (K)" 
         << setw(15) << "Cipher (Dec)" 
         << "Cipher (Hex)" << endl;
    cout << "--------------------------------------------------------------" << endl;
    
    for (int k = 0; k < print_limit; k++) {
        int m_ascii = (int)m[k];
        int k_val = key_stream[k];
        int c_val = ciphertext[k];
        
        cout << left << setw(10) << m[k] 
             << setw(10) << m_ascii 
             << setw(15) << k_val 
             << setw(15) << c_val 
             << "0x" << hex << uppercase << c_val << dec << endl;
    }

    return 0;
}