/*
 * filename: ezil.h
 */
#ifndef __EZIL_H__
#define __EZIL_H__

struct EzilHashrate
{
  int current_hashrate;
  int average_hashrate;
  int last_share_timestamp;
  String last_share_coin;
  String wallet;
  int reported_hashrate;
};

#endif
