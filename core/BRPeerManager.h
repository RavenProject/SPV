//
//  BRPeerManager.h
//
//  Created by Aaron Voisine on 9/2/15.
//  Copyright (c) 2015 breadwallet LLC.
//  Update by Roshii on 4/1/18.
//  Copyright (c) 2018 ravencoin core team
//

#ifndef BRPeerManager_h
#define BRPeerManager_h

#include "BRPeer.h"
#include "BRMerkleBlock.h"
#include "BRTransaction.h"
#include "BRWallet.h"
#include <stddef.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PEER_MAX_CONNECTIONS 6

typedef struct { uint32_t height; UInt256 hash; uint32_t timestamp; uint32_t target; } BRCheckPoint;

typedef struct {
    const char **dnsSeeds; // NULL terminated array of dns seeds
    uint16_t standardPort;
    uint32_t magicNumber;
    uint64_t services;
    int (*verifyDifficulty)(const BRMerkleBlock *block, const BRMerkleBlock *previous, uint32_t transitionTime);
    const BRCheckPoint *checkpoints;
    size_t checkpointsCount;
} BRChainParams;

typedef struct BRPeerManagerStruct BRPeerManager;

// returns a newly allocated PeerManager struct that must be freed by calling PeerManagerFree()
BRPeerManager *BRPeerManagerNew(const BRChainParams *params, BRWallet *wallet, uint32_t earliestKeyTime,
                                BRMerkleBlock *blocks[], size_t blocksCount, const BRPeer peers[], size_t peersCount);

// not thread-safe, set callbacks once before calling PeerManagerConnect()
// info is a void pointer that will be passed along with each callback call
// void syncStarted(void *) - called when blockchain syncing starts
// void syncStopped(void *, int) - called when blockchain syncing stops, error is an errno.h code
// void txStatusUpdate(void *) - called when transaction status may have changed such as when a new block arrives
// void saveBlocks(void *, int, MerkleBlock *[], size_t) - called when blocks should be saved to the persistent store
// - if replace is true, remove any previously saved blocks first
// void savePeers(void *, int, const Peer[], size_t) - called when peers should be saved to the persistent store
// - if replace is true, remove any previously saved peers first
// int networkIsReachable(void *) - must return true when networking is available, false otherwise
// void threadCleanup(void *) - called before a thread terminates to faciliate any needed cleanup
void BRPeerManagerSetCallbacks(BRPeerManager *manager, void *info,
                               void (*syncStarted)(void *info),
                               void (*syncStopped)(void *info, int error),
                               void (*txStatusUpdate)(void *info),
                               void (*saveBlocks)(void *info, int replace, BRMerkleBlock *blocks[], size_t blocksCount),
                               void (*savePeers)(void *info, int replace, const BRPeer peers[], size_t peersCount),
                               int (*networkIsReachable)(void *info),
                               void (*threadCleanup)(void *info));

// specifies a single fixed peer to use when connecting to the bitcoin network
// set address to UINT128_ZERO to revert to default behavior
void BRPeerManagerSetFixedPeer(BRPeerManager *manager, UInt128 address, uint16_t port);

// current connect status
BRPeerStatus BRPeerManagerConnectStatus(BRPeerManager *manager);

// true if currently connected to at least one peer
int BRPeerManagerIsConnected(BRPeerManager *manager);

// connect to bitcoin peer-to-peer network (also call this whenever networkIsReachable() status changes)
void BRPeerManagerConnect(BRPeerManager *manager);

// disconnect from bitcoin peer-to-peer network (may cause syncFailed(), saveBlocks() or savePeers() callbacks to fire)
void BRPeerManagerDisconnect(BRPeerManager *manager);

// rescans blocks and transactions after earliestKeyTime (a new random download peer is also selected due to the
// possibility that a malicious node might lie by omitting transactions that match the bloom filter)
void BRPeerManagerRescan(BRPeerManager *manager);

// rescans blocks and transactions after the last hardcoded checkpoint (uses a new random download peer, see above comment)
void BRPeerManagerRescanFromLastHardcodedCheckpoint(BRPeerManager *manager);

// rescans blocks and transactions from after the blockNumber.  If blockNumber is not known, then
// rescan from the just prior checkpoint (uses a new random download peer, see above comment).
void BRPeerManagerRescanFromBlockNumber(BRPeerManager *manager, uint32_t blockNumber);

// the (unverified) best block height reported by connected peers
uint32_t BRPeerManagerEstimatedBlockHeight(BRPeerManager *manager);

// current proof-of-work verified best block height
uint32_t BRPeerManagerLastBlockHeight(BRPeerManager *manager);

// current proof-of-work verified best block timestamp (time interval since unix epoch)
uint32_t BRPeerManagerLastBlockTimestamp(BRPeerManager *manager);

// current network sync progress from 0 to 1
// startHeight is the block height of the most recent fully completed sync
double BRPeerManagerSyncProgress(BRPeerManager *manager, uint32_t startHeight);

// returns the number of currently connected peers
size_t BRPeerManagerPeerCount(BRPeerManager *manager);

// description of the peer most recently used to sync blockchain data
const char *BRPeerManagerDownloadPeerName(BRPeerManager *manager);

// publishes tx to RAVENCOIN network (do not call TransactionFree() on tx afterward)
void BRPeerManagerPublishTx(BRPeerManager *manager, BRTransaction *tx, void *info,
                            void (*callback)(void *info, int error));

// number of connected peers that have relayed the given unconfirmed transaction
size_t BRPeerManagerRelayCount(BRPeerManager *manager, UInt256 txHash);

// return the ChainParams used to create this peer manager
const BRChainParams *BRPeerManagerChainParams(BRPeerManager *manager);

void PeerManagerGetAssetData(BRPeerManager *manager, void *infoManager, char *assetName, size_t nameLen,
                             void (*receivedAssetData)(void *info, BRAsset *asset));
    
// frees memory allocated for manager (call PeerManagerDisconnect() first if connected)
void BRPeerManagerFree(BRPeerManager *manager);

#ifdef __cplusplus
}
#endif

#endif // BRPeerManager_h
