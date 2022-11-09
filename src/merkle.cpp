#include "merkle.h"

std::string buildMerkle(std::vector<Transaction> &data) {

    bc::hash_list merkle;

    /**
* We need to iterate through every stored transaction, convert it's hash to bc::hash_digest and push to bc::hash_list
*/
    for (Transaction &tx: data) {
        /**
 * Convert string to the array of chars with the hash length + 1
 */
        char hashChar[65];

        for (int x = 0; x < sizeof(hashChar); x++)
            hashChar[x] = tx.getHash()[x];

        /**
* bc::hash_list stores bc::hash_digest values. So we need to find base16_literal value of every digested hash
*/
        bc::hash_digest decodedHash = bc::base16_literal(hashChar);

        merkle.push_back(decodedHash);
    }

    /**
* Stop if hash list is empty or contains one element
*/
    if (merkle.empty())
        return bc::encode_base16(bc::null_hash);
    else if (merkle.size() == 1)
        return bc::encode_base16(merkle[0]);
    /**
* While there is more than 1 hash in the list, keep looping...
*/
    while (merkle.size() > 1) {
        /**
*  If number of hashes is odd, duplicate last hash in the list.
*/
        if (merkle.size() % 2 != 0)
            merkle.push_back(merkle.back());
        /**
*   List size is now even.
*/
        assert(merkle.size() % 2 == 0);
        /**
*  New hash list.
*/
        bc::hash_list new_merkle;
        /**
*  Loop through hashes 2 at a time.
*/
        for (auto it = merkle.begin(); it != merkle.end(); it += 2) {
            /**
*  Join both current hashes together (concatenate).
*/
            bc::data_chunk concat_data(bc::hash_size * 2);
            auto concat = bc::serializer<
                    decltype(concat_data.begin())>(concat_data.begin());
            concat.write_hash(*it);
            concat.write_hash(*(it + 1));
            /**
*  Hash both of the hashes.
*/
            bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
            /**
*  Add this to the new list.
*/
            new_merkle.push_back(new_root);
        }
        /**
*  This is the new list.
*/
        merkle = new_merkle;

    }
    /**
*  Finally we end up with a single item.
*/
    return bc::encode_base16(merkle[0]);
}