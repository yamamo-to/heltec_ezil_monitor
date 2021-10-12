/*
 * filename: timezone.ino
 */

#define JST (3600 * 9)

void setupTime()
{
  configTime(JST, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
}
