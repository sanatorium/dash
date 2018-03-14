// Copyright (c) 2014-2017 The Dash Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPORK_H
#define SPORK_H

#include "hash.h"
#include "net.h"
#include "utilstrencodings.h"

class CSporkMessage;
class CSporkManager;

/*
    Don't ever reuse these IDs for other sporks
    - This would result in old clients getting confused about which spork is for what
*/
static const int SPORK_START                                            = 10001;
static const int SPORK_END                                              = 10013;

static const int SPORK_2_INSTANTSEND_ENABLED                            = 10001;
static const int SPORK_3_INSTANTSEND_BLOCK_FILTERING                    = 10002;
static const int SPORK_5_INSTANTSEND_MAX_VALUE                          = 10004;
static const int SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT                 = 10007;
static const int SPORK_9_SUPERBLOCKS_ENABLED                            = 10008;
static const int SPORK_10_MASTERNODE_PAY_UPDATED_NODES                  = 10009;
static const int SPORK_12_RECONSIDER_BLOCKS                             = 10011;
static const int SPORK_13_OLD_SUPERBLOCK_FLAG                           = 10012;
static const int SPORK_14_REQUIRE_SENTINEL_FLAG                         = 10013;

static const int64_t SPORK_2_INSTANTSEND_ENABLED_DEFAULT                = 0;            // ON
static const int64_t SPORK_3_INSTANTSEND_BLOCK_FILTERING_DEFAULT        = 0;            // ON
static const int64_t SPORK_5_INSTANTSEND_MAX_VALUE_DEFAULT              = 1000;         // 1000 SANITY
static const int64_t SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT_DEFAULT     = 0; // MODMOD ON (was 4070908800ULL;// OFF)
static const int64_t SPORK_9_SUPERBLOCKS_ENABLED_DEFAULT                = 4070908800ULL;// OFF
static const int64_t SPORK_10_MASTERNODE_PAY_UPDATED_NODES_DEFAULT      = 4070908800ULL;// OFF
static const int64_t SPORK_12_RECONSIDER_BLOCKS_DEFAULT                 = 0;            // 0 BLOCKS
static const int64_t SPORK_13_OLD_SUPERBLOCK_FLAG_DEFAULT               = 4070908800ULL;// OFF
static const int64_t SPORK_14_REQUIRE_SENTINEL_FLAG_DEFAULT             = 4070908800ULL;// OFF

/*
reference: https://dash-docs.github.io/en/developer-reference#get-tx
    10001 2 INSTANTSEND_ENABLED Turns on and off InstantSend network wide
    10002 3 INSTANTSEND_BLOCK_FILTERING Turns on and off InstantSend block filtering
    10004 5 INSTANTSEND_MAX_VALUE Controls the max value for an InstantSend transaction (currently 2000 dash)
    10007 8 MASTERNODE_PAYMENT_ENFORCEMENT Requires masternodes to be paid by miners when blocks are processed
    10008 9 SUPERBLOCKS_ENABLED Superblocks are enabled (10% of the block reward allocated to fund the dash treasury for funding approved proposals)
    10009 10 MASTERNODE_PAY_UPDATED_NODES Only current protocol version masternode’s will be paid (not older nodes)
    10011 12 RECONSIDER_BLOCKS Forces reindex of a specified number of blocks to recover from unintentional network forks
    10012 13 OLD_SUPERBLOCK_FLAG Deprecated. No network function since block 614820
    10013 14 REQUIRE_SENTINEL_FLAG Only masternode’s running sentinel will be paid
*/
extern std::map<uint256, CSporkMessage> mapSporks;
extern CSporkManager sporkManager;

//
// Spork classes
// Keep track of all of the network spork settings
//

class CSporkMessage
{
private:
    std::vector<unsigned char> vchSig;

public:
    int nSporkID;
    int64_t nValue;
    int64_t nTimeSigned;

    CSporkMessage(int nSporkID, int64_t nValue, int64_t nTimeSigned) :
        nSporkID(nSporkID),
        nValue(nValue),
        nTimeSigned(nTimeSigned)
        {}

    CSporkMessage() :
        nSporkID(0),
        nValue(0),
        nTimeSigned(0)
        {}


    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        READWRITE(nSporkID);
        READWRITE(nValue);
        READWRITE(nTimeSigned);
        READWRITE(vchSig);
    }

    uint256 GetHash() const
    {
        CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
        ss << nSporkID;
        ss << nValue;
        ss << nTimeSigned;
        return ss.GetHash();
    }

    bool Sign(std::string strSignKey);
    bool CheckSignature();
    void Relay(CConnman& connman);
};


class CSporkManager
{
private:
    std::vector<unsigned char> vchSig;
    std::string strMasterPrivKey;
    std::map<int, CSporkMessage> mapSporksActive;

public:

    CSporkManager() {}

    void ProcessSpork(CNode* pfrom, std::string& strCommand, CDataStream& vRecv, CConnman& connman);
    void ExecuteSpork(int nSporkID, int nValue);
    bool UpdateSpork(int nSporkID, int64_t nValue, CConnman& connman);

    bool IsSporkActive(int nSporkID);
    int64_t GetSporkValue(int nSporkID);
    int GetSporkIDByName(std::string strName);
    std::string GetSporkNameByID(int nSporkID);

    bool SetPrivKey(std::string strPrivKey);
};

#endif
