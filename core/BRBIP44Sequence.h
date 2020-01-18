//
//  BRBIP44Sequence.h
//
//  Created by Aaron Voisine on 8/19/15.
//  Copyright (c) 2015 breadwallet LLC
//  Update by Roshii on 4/1/18.
//  Copyright (c) 2018 ravencoin core team
//

#ifndef BRBIP34Sequence_h
#define BRBIP34Sequence_h

#include "BRKey.h"
#include "BRInt.h"
#include <stdarg.h>
#include <stddef.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

// BIP32 is a scheme for deriving chains of addresses from a seed value
// https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki

// BIP44 defines a logical HD wallet based on an algorithm described in BIP-0032
// https://github.com/bitcoin/bips/blob/master/bip-0044.mediawiki

#define BIP32_HARD                  0x80000000

#define BIP44_PURPOSE                   44
#define BIP44_RVN_COINTYPE              175
#define BIP44_DEFAULT_ACCOUNT           0

#define SEQUENCE_GAP_LIMIT_EXTERNAL     10
#define SEQUENCE_GAP_LIMIT_INTERNAL     5

#define SEQUENCE_EXTERNAL_CHAIN         0
#define SEQUENCE_INTERNAL_CHAIN         1

typedef struct {
    uint32_t fingerPrint;
    UInt256 chainCode;
    uint8_t pubKey[33];
} BRMasterPubKey;

#define MASTER_PUBKEY_NONE ((BRMasterPubKey) { 0, UINT256_ZERO, \
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } })

//static void _CKDpriv(UInt256 *k, UInt256 *c, uint32_t i);
//
//static void _CKDpub(ECPoint *K, UInt256 *c, uint32_t i);

// returns the master public key for the default BIP32 wallet layout - derivation path N(m/0H)
BRMasterPubKey BRBIP32MasterPubKey(const void *seed, size_t seedLen);

BRMasterPubKey BRBIP44MasterPubKey(const void *seed, size_t seedLen, uint32_t coinType, uint32_t account,
                                   const int isBip44DP);

// writes the public key for path N(m/0H/chain/index) to pubKey
// returns number of bytes written, or pubKeyLen needed if pubKey is NULL
size_t BRBIP32PubKey(uint8_t *pubKey, size_t pubKeyLen, BRMasterPubKey mpk, uint32_t chain, uint32_t index);

// sets the private key for path m/0H/chain/index to key
void BRBIP32PrivKey(BRKey *key, const void *seed, size_t seedLen, uint32_t chain, uint32_t index);

// sets the private key for path m/0H/chain/index to each element in keys
void BRBIP32PrivKeyList(BRKey *keys, size_t keysCount, const void *seed, size_t seedLen, uint32_t chain,
                        const uint32_t *indexes);

void BRBIP44PrivKeyList(BRKey *keys, size_t keysCount, const void *seed, size_t seedLen, uint32_t coinType,
                        uint32_t account, uint32_t chain, const uint32_t *indexes);
// sets the private key for the specified path to key
// depth is the number of arguments used to specify the path
void BRBIP32PrivKeyPath(BRKey *key, const void *seed, size_t seedLen, int depth, ...);

// sets the private key for the path specified by vlist to key
// depth is the number of arguments in vlist
void BRBIP32vPrivKeyPath(BRKey *key, const void *seed, size_t seedLen, int depth, va_list vlist);

// writes the base58check encoded serialized master private key (xprv) to str
// returns number of bytes written including NULL terminator, or strLen needed if str is NULL
size_t BRBIP32SerializeMasterPrivKey(char *str, size_t strLen, const void *seed, size_t seedLen);

// writes a master private key to seed given a base58check encoded serialized master private key (xprv)
// returns number of bytes written, or seedLen needed if seed is NULL
size_t BRBIP32ParseMasterPrivKey(void *seed, size_t seedLen, const char *str);

// writes the base58check encoded serialized master public key (xpub) to str
// returns number of bytes written including NULL terminator, or strLen needed if str is NULL
size_t BRBIP32SerializeMasterPubKey(char *str, size_t strLen, BRMasterPubKey mpk);

// returns a master public key give a base58check encoded serialized master public key (xpub)
BRMasterPubKey BRBIP32ParseMasterPubKey(const char *str);

// key used for authenticated API calls, i.e. bitauth: https://github.com/bitpay/bitauth - path m/1H/0
void BRBIP32APIAuthKey(BRKey *key, const void *seed, size_t seedLen);

// key used for BitID: https://github.com/bitid/bitid/blob/master/BIP_draft.md
void BRBIP32BitIDKey(BRKey *key, const void *seed, size_t seedLen, uint32_t index, const char *uri);

#ifdef __cplusplus
}
#endif

#endif // BRBIP44Sequence_h
