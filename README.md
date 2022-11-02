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

## User Interface

Once compiled, user will be presented with the following options:

```
Available commands:

help                   Show this help message
test                   Generate users & transactions to test blockchain
getblock <blockid>     Retrieve details of a mined block
omp                    Get number of available threads
exit                   exit the program
```

### Output
```
Mined block e

Block hash: 00000894b1f7baac212915048c3a11604def32b840f8c1d03dae4570242ebd18
Previous hash: 00000040919f61584abb4a6488e3d978e9a0dfd447745c6c171bbd64a1580120
Merkle root: 5832db28a63ececc43306254cef6a2684faf444cee25056462c4131c61b67d2c
Timestamp: 1667392479
Nonce: 178502
Difficulty: 5
Number of transactions: 51
```
```
Transaction list:

$1145.57  Hash: d475a03c1c2e7dbaf2d60e08fb0e1cec96ba5bbc66939778b75da650c33d78e8 From: 2f996fdc6f2b4c5409f4cd889236f65c2eadaa549e0a272477e02a40c0d462dc -> 87ac0bfc02ff19a4401ea92070cec658fb979d549d7680944405cb6475c8152c | Time: 1667392467
$16989.1  Hash: 6241809887317b74dce637b0cf31991caac52d90117682d0405d5e2c24012104 From: 21be6000a3c20d883ee1034881bcb6a8c62b9c40f82a816428d583bcde985264 -> 51352954c7929df88b771ed079db794ccc5f06e01f0883ecf6551a94ced528a0 | Time: 1667392467

[...]
```
```
User details:

user1 218983dcebcd7adc1353b784e7835164741317300d17ad2c4d6306f861a71b38 | $80318.3 -> $25301.3
user2 12e618504b108994365e0078471c9344b2513aa4e7b28d547b74ab6cfc7d82c4 | $12906.3 -> $72081.3

[...]
```

### Retrieve details of a mined block
```
./main getblock 20

Block hash: 00000cac770e83a4a169af486743f9d61b38d1884b227300f6a60d9c66b36184
Previous hash: 00000cb48a890f8467a249a83d2d744038629e606e07c340f2ac02a0728c398c
Merkle root: 89583e880432051085511ebca660f48cb99841148160e51865ceb848ef63c49c
Timestamp: 1667393340
Nonce: 1058887
Difficulty: 5
Number of transactions: 51

Transaction list:

$1897.73  Hash: d8138ba8cdc583f2aec68bb8bc86deca903ab044a7679f182b35d82c765e5ed0 From: bdd1c4881c6ec80cf7550e78676252f0d5a8946c24e2803c938bc0304312d414 -> f8a9b1d8c980e7645273265834eaee44623dbab83ad9d5c0f36b185c3cbfa538 | Time: 1667393302
$1182.47  Hash: 0e32c2f8b69de26e972bdb6c1adef7d8b0dc3ad49bb22ea872408218fd3b166c From: 10374684c222bdf4b82113d47bd2bec0cbb01848af297a0097868abc8d9ccbbc -> 54c4dce8311c3300ca4236e02f8bd9bce77464e059a4a65cde8668903378627c | Time: 1667393302

[...]

$15446.9  Hash: 50d6937ca18c575c052a180cc97da6d8f05bf520f5557518b4bb53809c070420 From: 739ea9ece941a558019825b08305c9b47ddb6b8cc22452d429b774846032f350 -> 5b934c10192f706835feed8c44ef2eb8b4366d34d3eab6e0b8a3fa34088a6d04 | Time: 1667393302
$82550.6  Hash: a675017457f37cc4e5ae0e905856f0d463ad06803548ce1058061b78656cdfc4 From: 3231dd24c8a88454c5f296f8aca7ba44547442089b67738cf6bdb48cd66b6518 -> 285ac3044dbe4be8c9e918f090d24248849d1088a359ca548a49665454dfd7a4 | Time: 1667393302
```