//
// BRScript.c
//
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
//

#include "BRScript.h"

// script opcodes: https://en.bitcoin.it/wiki/Script#Constants

const char *GetOpName(enum OPCODETYPE opcode) {
    switch (opcode) {
    case OP_0                      : return "0";
    case OP_PUSHDATA1              : return "OP_PUSHDATA1";
    case OP_PUSHDATA2              : return "OP_PUSHDATA2";
    case OP_PUSHDATA4              : return "OP_PUSHDATA4";
    case OP_1NEGATE                : return "-1";
    case OP_RESERVED               : return "OP_RESERVED";
    case OP_1                      : return "1";
    case OP_2                      : return "2";
    case OP_3                      : return "3";
    case OP_4                      : return "4";
    case OP_5                      : return "5";
    case OP_6                      : return "6";
    case OP_7                      : return "7";
    case OP_8                      : return "8";
    case OP_9                      : return "9";
    case OP_10                     : return "10";
    case OP_11                     : return "11";
    case OP_12                     : return "12";
    case OP_13                     : return "13";
    case OP_14                     : return "14";
    case OP_15                     : return "15";
    case OP_16                     : return "16";

    // control
    case OP_NOP                    : return "OP_NOP";
    case OP_VER                    : return "OP_VER";
    case OP_IF                     : return "OP_IF";
    case OP_NOTIF                  : return "OP_NOTIF";
    case OP_VERIF                  : return "OP_VERIF";
    case OP_VERNOTIF               : return "OP_VERNOTIF";
    case OP_ELSE                   : return "OP_ELSE";
    case OP_ENDIF                  : return "OP_ENDIF";
    case OP_VERIFY                 : return "OP_VERIFY";
    case OP_RETURN                 : return "OP_RETURN";

    // stack ops
    case OP_TOALTSTACK             : return "OP_TOALTSTACK";
    case OP_FROMALTSTACK           : return "OP_FROMALTSTACK";
    case OP_2DROP                  : return "OP_2DROP";
    case OP_2DUP                   : return "OP_2DUP";
    case OP_3DUP                   : return "OP_3DUP";
    case OP_2OVER                  : return "OP_2OVER";
    case OP_2ROT                   : return "OP_2ROT";
    case OP_2SWAP                  : return "OP_2SWAP";
    case OP_IFDUP                  : return "OP_IFDUP";
    case OP_DEPTH                  : return "OP_DEPTH";
    case OP_DROP                   : return "OP_DROP";
    case OP_DUP                    : return "OP_DUP";
    case OP_NIP                    : return "OP_NIP";
    case OP_OVER                   : return "OP_OVER";
    case OP_PICK                   : return "OP_PICK";
    case OP_ROLL                   : return "OP_ROLL";
    case OP_ROT                    : return "OP_ROT";
    case OP_SWAP                   : return "OP_SWAP";
    case OP_TUCK                   : return "OP_TUCK";

    // splice ops
    case OP_CAT                    : return "OP_CAT";
    case OP_SUBSTR                 : return "OP_SUBSTR";
    case OP_LEFT                   : return "OP_LEFT";
    case OP_RIGHT                  : return "OP_RIGHT";
    case OP_SIZE                   : return "OP_SIZE";

    // bit logic
    case OP_INVERT                 : return "OP_INVERT";
    case OP_AND                    : return "OP_AND";
    case OP_OR                     : return "OP_OR";
    case OP_XOR                    : return "OP_XOR";
    case OP_EQUAL                  : return "OP_EQUAL";
    case OP_EQUALVERIFY            : return "OP_EQUALVERIFY";
    case OP_RESERVED1              : return "OP_RESERVED1";
    case OP_RESERVED2              : return "OP_RESERVED2";

    // numeric
    case OP_1ADD                   : return "OP_1ADD";
    case OP_1SUB                   : return "OP_1SUB";
    case OP_2MUL                   : return "OP_2MUL";
    case OP_2DIV                   : return "OP_2DIV";
    case OP_NEGATE                 : return "OP_NEGATE";
    case OP_ABS                    : return "OP_ABS";
    case OP_NOT                    : return "OP_NOT";
    case OP_0NOTEQUAL              : return "OP_0NOTEQUAL";
    case OP_ADD                    : return "OP_ADD";
    case OP_SUB                    : return "OP_SUB";
    case OP_MUL                    : return "OP_MUL";
    case OP_DIV                    : return "OP_DIV";
    case OP_MOD                    : return "OP_MOD";
    case OP_LSHIFT                 : return "OP_LSHIFT";
    case OP_RSHIFT                 : return "OP_RSHIFT";
    case OP_BOOLAND                : return "OP_BOOLAND";
    case OP_BOOLOR                 : return "OP_BOOLOR";
    case OP_NUMEQUAL               : return "OP_NUMEQUAL";
    case OP_NUMEQUALVERIFY         : return "OP_NUMEQUALVERIFY";
    case OP_NUMNOTEQUAL            : return "OP_NUMNOTEQUAL";
    case OP_LESSTHAN               : return "OP_LESSTHAN";
    case OP_GREATERTHAN            : return "OP_GREATERTHAN";
    case OP_LESSTHANOREQUAL        : return "OP_LESSTHANOREQUAL";
    case OP_GREATERTHANOREQUAL     : return "OP_GREATERTHANOREQUAL";
    case OP_MIN                    : return "OP_MIN";
    case OP_MAX                    : return "OP_MAX";
    case OP_WITHIN                 : return "OP_WITHIN";

    // crypto
    case OP_RIPEMD160              : return "OP_RIPEMD160";
    case OP_SHA1                   : return "OP_SHA1";
    case OP_SHA256                 : return "OP_SHA256";
    case OP_HASH160                : return "OP_HASH160";
    case OP_HASH256                : return "OP_HASH256";
    case OP_CODESEPARATOR          : return "OP_CODESEPARATOR";
    case OP_CHECKSIG               : return "OP_CHECKSIG";
    case OP_CHECKSIGVERIFY         : return "OP_CHECKSIGVERIFY";
    case OP_CHECKMULTISIG          : return "OP_CHECKMULTISIG";
    case OP_CHECKMULTISIGVERIFY    : return "OP_CHECKMULTISIGVERIFY";

    // expansion
    case OP_NOP1                   : return "OP_NOP1";
    case OP_CHECKLOCKTIMEVERIFY    : return "OP_CHECKLOCKTIMEVERIFY";
    case OP_CHECKSEQUENCEVERIFY    : return "OP_CHECKSEQUENCEVERIFY";
    case OP_NOP4                   : return "OP_NOP4";
    case OP_NOP5                   : return "OP_NOP5";
    case OP_NOP6                   : return "OP_NOP6";
    case OP_NOP7                   : return "OP_NOP7";
    case OP_NOP8                   : return "OP_NOP8";
    case OP_NOP9                   : return "OP_NOP9";
    case OP_NOP10                  : return "OP_NOP10";

    // rvn
    case OP_RVN_ASSET              : return "OP_RVN_ASSET";

    case OP_INVALIDOPCODE          : return "OP_INVALIDOPCODE";

    default:
        return "OP_UNKNOWN";
    }
}

bool IsPayToPublicKeyHash(const uint8_t *script, size_t scriptLen) {

    return (scriptLen == 25 &&
	    script[0] == OP_DUP &&
	    script[1] == OP_HASH160 &&
	    script[2] == 0x14 &&
	    script[23] == OP_EQUALVERIFY &&
	    script[24] == OP_CHECKSIG);
}

bool IsPayToScriptHash(const uint8_t *script, size_t scriptLen) {

    return (scriptLen == 23 &&
            script[0] == OP_HASH160 &&
            script[1] == 0x14 &&
            script[22] == OP_EQUAL);
}

bool IsScriptNewAsset(const uint8_t *script, size_t scriptLen) {

    return (scriptLen > 39 &&
            script[25] == OP_RVN_ASSET &&
            script[27] == RVN_R &&
            script[28] == RVN_V &&
            script[29] == RVN_N &&
            script[30] == RVN_Q);// &&
//            script[scriptLen - 2] == OP_DROP);
}

bool IsScriptOwnerAsset(const uint8_t *script, size_t scriptLen) {

    bool helper = (scriptLen > 30 &&
            script[25] == OP_RVN_ASSET &&
            script[27] == RVN_R &&
            script[28] == RVN_V &&
            script[29] == RVN_N &&
            script[30] == RVN_O);// &&
            //script[scriptLen - 2] == OP_DROP);
    return helper;
}

bool IsScriptReissueAsset(const uint8_t *script, size_t scriptLen) {

    return (scriptLen > 30 &&
            script[25] == OP_RVN_ASSET &&
            script[27] == RVN_R &&
            script[28] == RVN_V &&
            script[29] == RVN_N &&
            script[30] == RVN_R);// &&
            //script[scriptLen - 2] == OP_DROP);
}

bool IsScriptTransferAsset(const uint8_t *script, size_t scriptLen) {

    bool helper = (scriptLen > 30 &&
            script[25] == OP_RVN_ASSET &&
            script[27] == RVN_R &&
            script[28] == RVN_V &&
            script[29] == RVN_N &&
            script[30] == RVN_T);// &&
           // script[scriptLen - 2] == OP_DROP);

    return helper;
}

//bool IsScriptOwnershipTransferAsset(const uint8_t *script, size_t scriptLen) {
//
//    bool helper = (scriptLen > 30 &&
//                   script[25] == OP_RVN_ASSET &&
//                   script[27] == RVN_R &&
//                   script[28] == RVN_V &&
//                   script[29] == RVN_N &&
//                   script[30] == RVN_T);// &&
//    // script[scriptLen - 2] == OP_DROP);
//
//    return helper;
//}

bool IsScriptAsset(const uint8_t *script, size_t scriptLen) {

    assert(script != NULL || scriptLen == 0);

    bool helper =  IsScriptTransferAsset(script, scriptLen) || IsScriptReissueAsset(script, scriptLen) ||
            IsScriptOwnerAsset(script, scriptLen) || IsScriptNewAsset(script, scriptLen);
    return helper;
}

bool IsAssetNameRootAsset(const BRAsset *asst) {

    assert(asst != NULL);
    assert(asst->name != NULL);

    if(strstr(asst->name, "/") || strstr(asst->name, "#"))
        return false;
    else return true;
}

bool IsAssetNameSubAsset(const BRAsset *asst) {

    assert(asst != NULL);
    assert(asst->name != NULL);

    if(strstr(asst->name, "/"))
        return true;
    else return false;
}

bool IsAssetNameUniqueAsset(const BRAsset *asst) {

    assert(asst != NULL);
    assert(asst->name != NULL);

    if(strstr(asst->name, "#"))
        return true;
    else return false;
}

bool IsPayToWitnessScriptHash(const uint8_t *script, size_t scriptLen) {

    return (scriptLen == 34 &&
            script[0] == OP_0 &&
            script[1] == 0x20);
}

bool IsPayToPublicKey(const uint8_t *script, size_t scriptLen) {

    // compressed or uncompressed pubkey
    if (scriptLen == 35) {
        return (script[1] == 0x02 || script[1] == 0x03) &&
                script[34] == OP_CHECKSIG;
    }
    if (scriptLen == 67) {
        return script[1] == 0x04 &&
                script[66] == OP_CHECKSIG;

    }
    return false;
}
