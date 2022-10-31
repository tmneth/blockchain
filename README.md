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
help: show this help message
getblock <blockhash>: retrieve details of a mined block 
gettransaction <transactionid>: retrieve details of a transaction 
stop: exit the program
```

### Retrieve details of a mined block

```zsh
getblock 000f0a16c78fde12b5e38d68f2c13782aa6a823c8666c7e8d84490043bbcf150
```

```zsh
Block hash: 000f0a16c78fde12b5e38d68f2c13782aa6a823c8666c7e8d84490043bbcf150
Previous hash: 00d5f0ccf0cd09f058727ba6bbe9d1aa422f02d0f2644894b3bb2a342453f0ac
Data hash: 7ae27ffc4166dbf849d0b2709742c03400cc72607f3dce64b08297cc17cfdbd4
Timestamp: 1666789089
Nonce: 101
Difficulty: 2
Number of transactions: 100
```

### Retrieve details of a transaction

```zsh
gettransaction 9999
```

```zsh
Id: 9999
From: 2eaaf52cad4656703e963aac4cad8704ed770450340248d0751f0360aeeaa148
To: 58ec92e8953ae840c18f4224a42e42c436a0ed7011ac9638d2476184a79de654
Transaction hash: c2383572313bb93edc23f67482d1597483757aa4168632004506af08fdfd779c
Amount: 8871.59
Timestamp: 1666789088
```

## Proof-of-Work

To mine a block, following properties are concatenated
and [hashed](https://github.com/tmneth/hash-generator) : `previous hash`, `data hash`, `timestamp` and `nonce`.

## Project Structure

```zsh
.
├── CMakeLists.txt
├── .gitignore
├── include
│   ├── blockchain.h
│   ├── block.h
│   ├── hash.h
│   ├── pool.h
│   ├── transaction.h
│   ├── user.h
│   └── utils.h
└── src
    ├── blockchain.cpp
    ├── block.cpp
    ├── hash.cpp
    ├── main.cpp
    ├── pool.cpp
    ├── transaction.cpp
    ├── user.cpp
    └── utils.cpp

```