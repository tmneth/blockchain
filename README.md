# Blockchain

My attempt to implement a simple blockchain.

## Project Setup

Clone the project

```zsh
git clone https://github.com/tmneth/blockchain.git
```

Compile the files

```
g++ src/*.cpp -o 'main' && ./main
```

### Output
When compiled, the process of mining is displayed
```
Thread 3 mined 0 block
Thread 0 mined 1 block

[...]

Thread 1 mined 42 block
Thread 2 mined 43 block
```
Afterwards, updated balances are printed
```
User details: 

Name: user0
Public key: 3ce34464557d24288f9101602a5ae6fc757183048d37b5346e18023cc7d2e788
Balance: 30061.2 -> 78720.1

[...]

Name: user99
Public key: 3210edbc79acf438784bee501cb3d55cb1cb9604e9a5f64c549681b4ec06e938
Balance: 44331 -> 21463.7
```
### Retrieve information of an individual block
Blocks are serialized in text files `block<xx>.txt` in the directory `blocks`

### Example `block6.txt`
```
Block hash: 0000cd8ed3c4e2448e582d2ad9a51cf42e322d50a6c17b4c6a0096a0f8bedc5c
Previous hash: 0000bff0ffb994f866ce0b9cef01390c9c634f94927f3c645a1934c8aa08cbb8
Merkle root: 981775248a1ba68cd966aa50463155a07d6b6d50c24563d04cde23a47eeca2b0
Timestamp: 1667579438
Nonce: 11680
Difficulty: 4
Number of transactions: 100

Transaction list: 
$12704    Hash: 1008443897bdfc98e9bdb3e817bc33dc1c6578a0ce2b443c24df5e3895042e44 From: edbc2ef480530ab80baefb3463ec20d8c6e7f47845f717e83295d53c6e9fcf88 -> c8b3f0f8d4499e58eafb28b441195d889090e0bc63d16dd080b3bd7c6510acd4 | Time: 1667579436
$58685.2  Hash: 55f3ca60d1c196803093a3f8eaffaad8725141f465630c1c73d382f09f5e48d0 From: bb8088640c1680285a508960556506fcde274704d27dc534ca5a723c15cb5f88 -> a2d57134877329a0639b02a804abbe948f81ecdc364af80ce8c3175cd51941e0 | Time: 1667579436

[...]

$2132.13  Hash: a0d8c5a28b9b2a528a0643f2f78fda1852da1d8cafbb54a4d87325b06df1f974 From: bc4dc510af0a73c0e7e51db4e47b8da404b8e26846c2ed68c4fb720c38bb01e4 -> 3b6e712cf1a5cf00d5079b34ece0d0d4b871d6508446f1c0c47a56a0c8ddda28 | Time: 1667579436
$3143.29  Hash: cfc2270a4616393cf6d6e7109445d8a802635bc80d82536029d5b8a8ba7d79dc From: e66c1bf44cc2aa60414ae470e1d678883127eb64732e7f74b02112d4e24b1cbc -> b59cd678a037ac3c52a4a598ad1261fcb23ab7ac4b6e8f24e440f244964d7aec | Time: 1667579436
```
