﻿#include "stdafx.h"
#include "Level.h"
#include "NET_Queue.h"

void CLevel::OnSecureMessage(NET_Packet& P)
{
    NET_Packet dec_packet;
    dec_packet.B.count = P.B.count - sizeof(u16) - sizeof(u32);   // - r_begin - crypt_check_sum
    P.r(dec_packet.B.data, dec_packet.B.count);
    u32 checksum      = secure_messaging::decrypt(dec_packet.B.data, dec_packet.B.count, m_secret_key);
    u32 real_checksum = 0;
    P.r_u32(real_checksum);
    VERIFY(checksum == real_checksum);   //cheater tries to change incoming data packet - need crash
    game_events->insert(dec_packet);     //if checksum != real_checksum will be delayed crash ...
}

void CLevel::OnSecureKeySync(NET_Packet& P)
{
    s32 new_seed = 0;
    P.r_s32(new_seed);
    secure_messaging::generate_key(new_seed, m_secret_key);
}

void CLevel::SecureSend(NET_Packet& P, u32 dwFlags, u32 dwTimeout)
{
    NET_Packet enc_packet;

    enc_packet.w_begin(M_SECURE_MESSAGE);
    u32 checksum = secure_messaging::encrypt(P.B.data, P.B.count, m_secret_key);
    enc_packet.w(P.B.data, P.B.count);
    enc_packet.w_u32(checksum);
    Send(enc_packet, dwFlags, dwTimeout);
}
