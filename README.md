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

## Various methods with examples

### getblockchaininfo

```json
{
        "name" : "main",
        "blocks" : 44,
        "headers" : 44,
        "difficulty" : 5
}
```

### getblock blockhash
```json
{
   "hash" : "0aa1fd840ad262806ab488a0c8687094f0129928395c2578b37c1e043d4ddefc",
   "height" : 21,
   "merkleroot" : "3ba03af4c8ff1554df81a1000150b8c0b192efb0b471ac04389ffd384e5f4364",
   "nTx" : 4,
   "nonce" : 51,
   "difficulty" : 5,
   "previousblockhash" : "0f0a74a88a86edc02313fac4740bbfb0fd8d995c7d486e3c13f50f90f5c9d7cc",
   "time" : 1667921184,
   "tx" : 
   [
      "4047066cc6a3d5d8d5342108a6e4969c007610bc43dd1ad4201aa7045329ffec",
      "003060f05ad2ed4a85a059e4082cd2269136e27cbae2a660586e597439c5d6ac",
      "570e58acc1f501c44add20788938dacc1fcde9c4fd56b1dc79a0bf282e901f98",
      "4a54d640ea3f6e9691cc2a86b220df68f6c93bd4d2af82941d44f3185db423f8"
   ]
}
```

### getrawtransaction txid
```json
{
        "txid" : "6245c1889badf9ec06b04fa444567d489811f2e8e58783f4a28f48444a434e0c",
        "amount" : 74388.035890019266,
        "from" : "ac4d124c3ef7934c86d44110f4eedb7c797748d8f7a432c4488dc3a414723b58",
        "to" : "396f07dcc70519149596a17c6b071270c6aa7b7c318b0090b33caae80f80c084",
        "time" : 1667927989,
}
```
