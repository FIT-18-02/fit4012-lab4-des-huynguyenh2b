/**
 * @file des.cpp
 * @brief Implementation of Data Encryption Standard (DES) and TripleDES (3DES).
 * * Includes operations for standard 64-bit block encryption and decryption,
 * zero-padding for multi-block data, and sequential TripleDES execution.
 */

#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

/**
 * @brief Converts a decimal integer to a 4-bit binary string.
 * @param decimal The integer to convert.
 * @return 4-bit binary string representation.
 */
string convert_decimal_to_binary(int decimal) {
    return bitset<4>(decimal).to_string();
}

/**
 * @brief Converts a binary string to a decimal integer.
 * @param binary The binary string to convert.
 * @return Decimal integer representation.
 */
int convert_binary_to_decimal(const string& binary) {
    return stoi(binary, nullptr, 2);
}

/**
 * @brief Performs a bitwise XOR operation between two binary strings of equal length.
 * @param a First binary string.
 * @param b Second binary string.
 * @return The resulting binary string after XOR.
 */
string Xor(const string& a, const string& b) {
    string result = "";
    for (size_t i = 0; i < b.size(); i++) {
        result += (a[i] != b[i]) ? '1': '0';
    }
    return result;
}

/**
 * @brief Applies the Initial Permutation (IP) to a 64-bit block.
 * @param input 64-bit binary string.
 * @return 64-bit permuted binary string.
 */
string initial_permutation(const string& input) {
    const int initial_permutation_table[64] = {
        58,50,42,34,26,18,10,2, 60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6, 64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,  59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5, 63,55,47,39,31,23,15,7
    };

    string permuted = "";
    for (int i = 0; i < 64; i++) {
        permuted += input[initial_permutation_table[i] - 1];
    }
    return permuted;
}

/**
 * @brief Applies the Inverse Initial Permutation (IP^-1) to a 64-bit block.
 * @param input 64-bit binary string.
 * @return 64-bit permuted binary string.
 */
string inverse_initial_permutation(const string& input) {
    const int inverse_permutation_table[64] = {
        40,8,48,16,56,24,64,32, 39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30, 37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28, 35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26, 33,1,41,9,49,17,57,25
    };

    string permuted = "";
    for (int i = 0; i < 64; i++) {
        permuted += input[inverse_permutation_table[i] - 1];
    }
    return permuted;
}

/**
 * @class KeyGenerator
 * @brief Handles the generation of 16 round keys from a 64-bit initial key.
 */
class KeyGenerator {
private:
    string key;
    vector<string> roundKeys;

    const int pc1[56] = {
        57,49,41,33,25,17,9,  1,58,50,42,34,26,18,
        10,2,59,51,43,35,27,  19,11,3,60,52,44,36,
        63,55,47,39,31,23,15, 7,62,54,46,38,30,22,
        14,6,61,53,45,37,29,  21,13,5,28,20,12,4
    };

    const int pc2[48] = {
        14,17,11,24,1,5,    3,28,15,6,21,10,
        23,19,12,4,26,8,    16,7,27,20,13,2,
        41,52,31,37,47,55,  30,40,51,45,33,48,
        44,49,39,56,34,53,  46,42,50,36,29,32
    };

    string shift_left_once(const string& key_chunk) {
        return key_chunk.substr(1) + key_chunk[0];
    }

    string shift_left_twice(string key_chunk) {
        key_chunk = shift_left_once(key_chunk);
        return shift_left_once(key_chunk);
    }

public:
    KeyGenerator(const string& input_key) : key(input_key) {}

    void generateRoundKeys() {
        roundKeys.clear();
        string permutedKey = "";
        for (int i = 0; i < 56; ++i) {
            permutedKey += key[pc1[i] - 1];
        }

        string left = permutedKey.substr(0, 28);
        string right = permutedKey.substr(28, 28);

        for (int i = 0; i < 16; ++i) {
            if (i == 0 || i == 1 || i == 8 || i == 15) {
                left = shift_left_once(left);
                right = shift_left_once(right);
            } else {
                left = shift_left_twice(left);
                right = shift_left_twice(right);
            }

            string combinedKey = left + right;
            string roundKey = "";
            for (int j = 0; j < 48; ++j) {
                roundKey += combinedKey[pc2[j] - 1];
            }
            roundKeys.push_back(roundKey);
        }
    }

    const vector<string>& getRoundKeys() const {
        return roundKeys;
    }
};

/**
 * @class DES
 * @brief Core processor for executing Feistel network rounds for DES algorithms.
 */
class DES {
private:
    const int expansion_table[48] = {
        32,1,2,3,4,5,4,5,       6,7,8,9,8,9,10,11,
        12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,
        22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1
    };

    const int permutation_tab[32] = {
        16,7,20,21,29,12,28,17, 1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,    19,13,30,6,22,11,4,25
    };

    const int substition_boxes[8][4][16] = {
        { {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7}, {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8}, {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} },
        { {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10}, {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5}, {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15}, {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9} },
        { {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8}, {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1}, {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7}, {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12} },
        { {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15}, {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9}, {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4}, {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14} },
        { {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9}, {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6}, {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14}, {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3} },
        { {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11}, {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8}, {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6}, {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13} },
        { {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1}, {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6}, {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2}, {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12} },
        { {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7}, {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2}, {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8}, {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} }
    };

    vector<string> round_keys;

    /**
     * @brief Core generalized method for 16 Feistel rounds.
     * @param input 64-bit plaintext or ciphertext block.
     * @param is_encrypt Dictates the loop direction for the keys (Forward: 1-16, Backward: 16-1).
     * @return Processed 64-bit block.
     * * @note Logic: Reusing the same pipeline ensures robust handling of both encryption
     * and decryption without duplicated logic, reducing potential syntax bugs.
     */
    string process_block(const string& input, bool is_encrypt) {
        string perm = initial_permutation(input);
        string left = perm.substr(0, 32);
        string right = perm.substr(32, 32);

        int start = is_encrypt ? 0 : 15;
        int end = is_encrypt ? 16 : -1;
        int step = is_encrypt ? 1 : -1;

        for (int i = start; i != end; i += step) {
            string right_expanded = "";
            for (int j = 0; j < 48; j++) {
                right_expanded += right[expansion_table[j] - 1];
            }

            string xored = Xor(round_keys[i], right_expanded);

            string res = "";
            for (int j = 0; j < 8; j++) {
                string row1 = xored.substr(j * 6, 1) + xored.substr(j * 6 + 5, 1);
                int row = convert_binary_to_decimal(row1);

                string col1 = xored.substr(j * 6 + 1, 4);
                int col = convert_binary_to_decimal(col1);

                int val = substition_boxes[j][row][col];
                res += convert_decimal_to_binary(val);
            }

            string perm2 = "";
            for (int j = 0; j < 32; j++) {
                perm2 += res[permutation_tab[j] - 1];
            }

            string new_right = Xor(perm2, left);
            left = right;
            right = new_right;
        }

        string combined_text = right + left;
        return inverse_initial_permutation(combined_text);
    }

public:
    DES(const vector<string>& keys) : round_keys(keys) {}

    string encrypt(const string& input) {
        return process_block(input, true);
    }

    string decrypt(const string& input) {
        return process_block(input, false);
    }
};

int main() {
    int mode;
    if (!(cin >> mode)) return 0;

    if (mode == 1) { // DES Encrypt
        string plaintext, key;
        cin >> plaintext >> key;

        // Zero Padding
        while (plaintext.length() % 64 != 0) {
            plaintext += "0";
        }

        KeyGenerator keygen(key);
        keygen.generateRoundKeys();
        DES des(keygen.getRoundKeys());

        string ciphertext = "";
        for (size_t i = 0; i < plaintext.length(); i += 64) {
            ciphertext += des.encrypt(plaintext.substr(i, 64));
        }
        cout << ciphertext << endl;

    } else if (mode == 2) { // DES Decrypt
        string ciphertext, key;
        cin >> ciphertext >> key;

        KeyGenerator keygen(key);
        keygen.generateRoundKeys();
        DES des(keygen.getRoundKeys());

        string plaintext = "";
        for (size_t i = 0; i < ciphertext.length(); i += 64) {
            plaintext += des.decrypt(ciphertext.substr(i, 64));
        }
        cout << plaintext << endl;

    } else if (mode == 3) { // TripleDES Encrypt (E(K3, D(K2, E(K1, P))))
        string plaintext, k1, k2, k3;
        cin >> plaintext >> k1 >> k2 >> k3;

        KeyGenerator kg1(k1); kg1.generateRoundKeys(); DES des1(kg1.getRoundKeys());
        KeyGenerator kg2(k2); kg2.generateRoundKeys(); DES des2(kg2.getRoundKeys());
        KeyGenerator kg3(k3); kg3.generateRoundKeys(); DES des3(kg3.getRoundKeys());

        string ciphertext = "";
        for (size_t i = 0; i < plaintext.length(); i += 64) {
            string block = plaintext.substr(i, 64);
            string c1 = des1.encrypt(block);
            string p2 = des2.decrypt(c1);
            string c3 = des3.encrypt(p2);
            ciphertext += c3;
        }
        cout << ciphertext << endl;

    } else if (mode == 4) { // TripleDES Decrypt (D(K1, E(K2, D(K3, C))))
        string ciphertext, k1, k2, k3;
        cin >> ciphertext >> k1 >> k2 >> k3;

        KeyGenerator kg1(k1); kg1.generateRoundKeys(); DES des1(kg1.getRoundKeys());
        KeyGenerator kg2(k2); kg2.generateRoundKeys(); DES des2(kg2.getRoundKeys());
        KeyGenerator kg3(k3); kg3.generateRoundKeys(); DES des3(kg3.getRoundKeys());

        string plaintext = "";
        for (size_t i = 0; i < ciphertext.length(); i += 64) {
            string block = ciphertext.substr(i, 64);
            string p1 = des3.decrypt(block);
            string c2 = des2.encrypt(p1);
            string p3 = des1.decrypt(c2);
            plaintext += p3;
        }
        cout << plaintext << endl;
    }

    return 0;
}