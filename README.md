# Blockchain

My attempt to implement a simple blockchain.

## Project Setup

Clone the project

```zsh
git clone https://github.com/tmneth/blockchain.git
```

Compile the files

```
cmake -B _builds && make -C _builds
```

## Merkle Tree

This blockchain uses slightly modified Merkle Tree implementation from [libbitcoin-system](https://github.com/libbitcoin/libbitcoin-system)

### What's different?

- Function return value is changed to std::string, therefore `bc::hash_digest` elements are base16 encoded
- To form `bc::hash_list`, hash of every transaction is converted into 65 char array that is subsequently converted to base16 literal
- Finally, `bc::hash_digest` value is then pushed to `bc::hash_list`

## Command-line interface

- `help` - Displays available commands.
- `initchain` - initializes and serializes blockchain.
- `getblockchaininfo` - Returns an object containing various state info.
- `getblock <hash>` - Returns information about the block with the given hash.
- `getrawtransaction <txid>` - Returns raw transaction representation for given transaction id.

### Various methods with examples

`$ ./bin getblockchaininfo`

```json
{
  "chain": "main",
  "bestblockhash": "0e1d2c3cb4f2db98a4fecd3c14127a184a19ee4c37e3b2d0f2e59c64b70e0d10",
  "blocks": 42,
  "headers": 42,
  "difficulty": 1
}
```

`$ ./bin getblock 03cc398c40f548c0597d536c13320d54fb18d6ccabea7a74c198f26421cce018`

```json
{
  "hash": "03cc398c40f548c0597d536c13320d54fb18d6ccabea7a74c198f26421cce018",
  "height": 44,
  "merkleroot": "c5896de036552910d0418fb0eb8bf89c0670b0f8b1d730487d9e64fc1075f2f8",
  "nTx": 9,
  "nonce": 11,
  "difficulty": 1,
  "previousblockhash": "047885246d82510c1eda646469777a784e290238b8dc17b0c6fa3ec03f46eb90",
  "time": 1667930841,
  "tx": [
    "e863675c72a63104c303ff40e28b0bb0b46a08f8b4ca1690252c3ecc984305d0",
    "ca5ed564803f28f6936122a42c6ae72aacb5a9dc8ab6a870ea2fb0fcf7aa84ac",
    "e43ca0d494d73d44664f2bd0f60098347b0b7bfce2adfed8adf748742cc1d104",
    "3e175d388b86ddbc0361ffb499b117043741660c74eb3c68efe8b7748164f830",
    "2a2bc84cdfde24d0ef0ebf5c4733f1d87814ab640e75b2ac1f2924a82c75d210",
    "9d0a707c3e61e3480e68f9a404ef9e0471073c9060362168d4850484156b51f8",
    "355977c40a1e66740d2b2340cc05531cf6ff83542741b63c85d7900cd31288f8",
    "649f9dd8b1b96c6887cb7c8cd72c52744ad81aa8850da7e46d1179349f383d4c",
    "02d94a487c190b44123366903eb123e0a3b6ed8cb72c50743afcf59c41f22dcc"
  ]
}
```

`$ ./bin getrawtransaction 22f8fb70615650a0c4f3f958333ec59cc6deca7056c97038f9eee6c44e7b7ecc`

```json
{
  "txid": "22f8fb70615650a0c4f3f958333ec59cc6deca7056c97038f9eee6c44e7b7ecc",
  "amount": 52737.662490191993,
  "from": "6fffe7f8b57207b8fd2a4950f6edb7149f7a3060168c506ca702f8d8d0d3070c",
  "time": 1667930839,
  "to": "8dee0f9c405d244840404ab8ee9cab9cf2a5379844d13dbcd6d5410c6652c670"
}
```
