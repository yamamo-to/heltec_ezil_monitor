/*
 * filename: util.ino
 */
String unquote(String quoted)
{
  int len = quoted.length();
  if (len >= 2)
  {
    if (quoted[0] == '"' && quoted[len - 1] == '"')
    {
      return quoted.substring(1, len - 1);
    }
  }
  return quoted;
}

String tm2string(struct tm *tm)
{
  char s[25];
  static const char *wd[7] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};
  sprintf(s, "%04d/%02d/%02d(%s) %02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, wd[tm->tm_wday], tm->tm_hour, tm->tm_min);
  String ss(s);
  return ss;
}
