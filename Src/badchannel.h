
bool isbadchannel(TString statringname, int rhidsmall){


  int endcap = (rhidsmall<400)? 1:2;
  if(rhidsmall>400) rhidsmall -=400;

  int layer = rhidsmall%10;
  int chamber = floor(rhidsmall/10);

if(statringname.Index("ME11a")>=0&&endcap== 1 &&chamber== 3 &&layer== 1 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 1 &&chamber== 3 &&layer== 3 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 1 &&chamber== 7 &&layer== 4 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 2 &&layer== 6 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 4 &&layer== 1 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 4 &&layer== 2 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 4 &&layer== 3 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 4 &&layer== 4 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 5 &&layer== 2 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 7 &&layer== 1 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 9 &&layer== 1 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 9 &&layer== 2 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 18 &&layer== 6 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 25 &&layer== 4 )return true;
if(statringname.Index("ME11a")>=0&&endcap== 2 &&chamber== 25 &&layer== 6 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 1 &&chamber== 15 &&layer== 1 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 1 &&chamber== 36 &&layer== 1 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 2 &&layer== 6 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 4 &&layer== 1 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 4 &&layer== 2 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 4 &&layer== 3 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 4 &&layer== 4 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 5 &&layer== 2 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 7 &&layer== 1 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 9 &&layer== 1 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 9 &&layer== 2 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 18 &&layer== 6 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 25 &&layer== 4 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 25 &&layer== 6 )return true;
if(statringname.Index("ME11b")>=0&&endcap== 2 &&chamber== 30 &&layer== 4 )return true;
if(statringname.Index("ME13HV1")>=0&&endcap== 1 &&chamber== 15 &&layer== 1 )return true;
if(statringname.Index("ME13HV1")>=0&&endcap== 1 &&chamber== 15 &&layer== 2 )return true;
if(statringname.Index("ME13HV1")>=0&&endcap== 1 &&chamber== 15 &&layer== 3 )return true;
if(statringname.Index("ME13HV1")>=0&&endcap== 1 &&chamber== 15 &&layer== 4 )return true;
if(statringname.Index("ME13HV1")>=0&&endcap== 1 &&chamber== 15 &&layer== 5 )return true;
if(statringname.Index("ME13HV1")>=0&&endcap== 1 &&chamber== 15 &&layer== 6 )return true;
if(statringname.Index("ME13HV1")>=0&&endcap== 1 &&chamber== 16 &&layer== 2 )return true;
if(statringname.Index("ME13HV1")>=0&&endcap== 1 &&chamber== 16 &&layer== 3 )return true;
if(statringname.Index("ME13HV1")>=0&&endcap== 1 &&chamber== 16 &&layer== 6 )return true;
if(statringname.Index("ME13HV1")>=0&&endcap== 2 &&chamber== 20 &&layer== 1 )return true;
if(statringname.Index("ME13HV2")>=0&&endcap== 1 &&chamber== 15 &&layer== 1 )return true;
if(statringname.Index("ME13HV2")>=0&&endcap== 1 &&chamber== 15 &&layer== 2 )return true;
if(statringname.Index("ME13HV2")>=0&&endcap== 1 &&chamber== 15 &&layer== 4 )return true;
if(statringname.Index("ME13HV2")>=0&&endcap== 1 &&chamber== 15 &&layer== 6 )return true;
if(statringname.Index("ME13HV2")>=0&&endcap== 1 &&chamber== 16 &&layer== 1 )return true;
if(statringname.Index("ME13HV2")>=0&&endcap== 1 &&chamber== 16 &&layer== 2 )return true;
if(statringname.Index("ME13HV2")>=0&&endcap== 1 &&chamber== 16 &&layer== 6 )return true;
if(statringname.Index("ME13HV3")>=0&&endcap== 1 &&chamber== 15 &&layer== 1 )return true;
if(statringname.Index("ME13HV3")>=0&&endcap== 1 &&chamber== 15 &&layer== 2 )return true;
if(statringname.Index("ME13HV3")>=0&&endcap== 1 &&chamber== 15 &&layer== 4 )return true;
if(statringname.Index("ME13HV3")>=0&&endcap== 1 &&chamber== 15 &&layer== 5 )return true;
if(statringname.Index("ME13HV3")>=0&&endcap== 1 &&chamber== 15 &&layer== 6 )return true;
if(statringname.Index("ME13HV3")>=0&&endcap== 1 &&chamber== 16 &&layer== 5 )return true;
if(statringname.Index("ME13HV3")>=0&&endcap== 1 &&chamber== 16 &&layer== 6 )return true;
if(statringname.Index("ME13HV3")>=0&&endcap== 2 &&chamber== 4 &&layer== 5 )return true;
if(statringname.Index("ME13HV3")>=0&&endcap== 2 &&chamber== 20 &&layer== 1 )return true;
if(statringname.Index("ME13HV3")>=0&&endcap== 2 &&chamber== 24 &&layer== 6 )return true;
if(statringname.Index("ME21HV1")>=0&&endcap== 1 &&chamber== 7 &&layer== 2 )return true;
if(statringname.Index("ME21HV2")>=0&&endcap== 1 &&chamber== 13 &&layer== 6 )return true;
if(statringname.Index("ME21HV2")>=0&&endcap== 1 &&chamber== 16 &&layer== 5 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 19 &&layer== 1 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 19 &&layer== 2 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 19 &&layer== 3 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 19 &&layer== 4 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 19 &&layer== 5 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 19 &&layer== 6 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 20 &&layer== 1 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 20 &&layer== 2 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 20 &&layer== 3 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 20 &&layer== 4 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 20 &&layer== 5 )return true;
if(statringname.Index("ME22HV1")>=0&&endcap== 2 &&chamber== 20 &&layer== 6 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 1 &&chamber== 1 &&layer== 2 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 2 &&chamber== 19 &&layer== 1 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 2 &&chamber== 19 &&layer== 2 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 2 &&chamber== 19 &&layer== 3 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 2 &&chamber== 19 &&layer== 4 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 2 &&chamber== 19 &&layer== 5 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 2 &&chamber== 19 &&layer== 6 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 2 &&chamber== 20 &&layer== 2 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 2 &&chamber== 20 &&layer== 3 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 2 &&chamber== 20 &&layer== 4 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 2 &&chamber== 20 &&layer== 6 )return true;
if(statringname.Index("ME22HV2")>=0&&endcap== 2 &&chamber== 26 &&layer== 6 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 1 &&chamber== 1 &&layer== 5 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 2 &&chamber== 19 &&layer== 1 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 2 &&chamber== 19 &&layer== 2 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 2 &&chamber== 19 &&layer== 3 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 2 &&chamber== 19 &&layer== 4 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 2 &&chamber== 19 &&layer== 5 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 2 &&chamber== 19 &&layer== 6 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 2 &&chamber== 20 &&layer== 2 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 2 &&chamber== 20 &&layer== 3 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 2 &&chamber== 20 &&layer== 4 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 2 &&chamber== 20 &&layer== 6 )return true;
if(statringname.Index("ME22HV3")>=0&&endcap== 2 &&chamber== 27 &&layer== 6 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 1 &&chamber== 1 &&layer== 4 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 1 &&chamber== 1 &&layer== 6 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 19 &&layer== 1 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 19 &&layer== 2 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 19 &&layer== 3 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 19 &&layer== 4 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 19 &&layer== 5 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 19 &&layer== 6 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 20 &&layer== 2 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 20 &&layer== 3 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 20 &&layer== 4 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 20 &&layer== 5 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 20 &&layer== 6 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 27 &&layer== 4 )return true;
if(statringname.Index("ME22HV4")>=0&&endcap== 2 &&chamber== 27 &&layer== 6 )return true;
if(statringname.Index("ME22HV5")>=0&&endcap== 2 &&chamber== 19 &&layer== 4 )return true;
if(statringname.Index("ME22HV5")>=0&&endcap== 2 &&chamber== 19 &&layer== 6 )return true;
if(statringname.Index("ME22HV5")>=0&&endcap== 2 &&chamber== 20 &&layer== 1 )return true;
if(statringname.Index("ME22HV5")>=0&&endcap== 2 &&chamber== 20 &&layer== 2 )return true;
if(statringname.Index("ME22HV5")>=0&&endcap== 2 &&chamber== 20 &&layer== 3 )return true;
if(statringname.Index("ME22HV5")>=0&&endcap== 2 &&chamber== 20 &&layer== 4 )return true;
if(statringname.Index("ME22HV5")>=0&&endcap== 2 &&chamber== 20 &&layer== 6 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 1 &&chamber== 8 &&layer== 1 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 1 &&chamber== 8 &&layer== 4 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 1 &&chamber== 8 &&layer== 5 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 1 &&chamber== 8 &&layer== 6 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 1 &&chamber== 9 &&layer== 1 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 1 &&chamber== 9 &&layer== 4 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 1 &&chamber== 9 &&layer== 5 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 2 &&chamber== 3 &&layer== 4 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 2 &&chamber== 15 &&layer== 1 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 2 &&chamber== 15 &&layer== 5 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 2 &&chamber== 15 &&layer== 6 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 2 &&chamber== 16 &&layer== 1 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 2 &&chamber== 16 &&layer== 5 )return true;
if(statringname.Index("ME31HV1")>=0&&endcap== 2 &&chamber== 16 &&layer== 6 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 1 &&chamber== 8 &&layer== 1 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 1 &&chamber== 8 &&layer== 3 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 1 &&chamber== 8 &&layer== 4 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 1 &&chamber== 8 &&layer== 5 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 1 &&chamber== 8 &&layer== 6 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 1 &&chamber== 9 &&layer== 1 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 1 &&chamber== 9 &&layer== 3 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 1 &&chamber== 9 &&layer== 4 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 1 &&chamber== 9 &&layer== 5 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 1 &&chamber== 9 &&layer== 6 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 1 &&chamber== 18 &&layer== 2 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 6 &&layer== 3 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 15 &&layer== 1 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 15 &&layer== 2 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 15 &&layer== 3 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 15 &&layer== 4 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 15 &&layer== 5 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 15 &&layer== 6 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 16 &&layer== 1 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 16 &&layer== 2 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 16 &&layer== 3 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 16 &&layer== 4 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 16 &&layer== 5 )return true;
if(statringname.Index("ME31HV2")>=0&&endcap== 2 &&chamber== 16 &&layer== 6 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 8 &&layer== 2 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 8 &&layer== 3 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 8 &&layer== 4 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 8 &&layer== 5 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 8 &&layer== 6 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 9 &&layer== 1 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 9 &&layer== 2 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 9 &&layer== 3 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 9 &&layer== 4 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 9 &&layer== 5 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 9 &&layer== 6 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 14 &&layer== 6 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 1 &&chamber== 18 &&layer== 2 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 2 &&chamber== 6 &&layer== 3 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 2 &&chamber== 15 &&layer== 1 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 2 &&chamber== 15 &&layer== 3 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 2 &&chamber== 15 &&layer== 4 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 2 &&chamber== 15 &&layer== 5 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 2 &&chamber== 15 &&layer== 6 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 2 &&chamber== 16 &&layer== 1 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 2 &&chamber== 16 &&layer== 3 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 2 &&chamber== 16 &&layer== 4 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 2 &&chamber== 16 &&layer== 5 )return true;
if(statringname.Index("ME31HV3")>=0&&endcap== 2 &&chamber== 16 &&layer== 6 )return true;
if(statringname.Index("ME41HV1")>=0&&endcap== 2 &&chamber== 3 &&layer== 2 )return true;
if(statringname.Index("ME41HV1")>=0&&endcap== 2 &&chamber== 8 &&layer== 1 )return true;
if(statringname.Index("ME41HV1")>=0&&endcap== 2 &&chamber== 8 &&layer== 2 )return true;
if(statringname.Index("ME41HV1")>=0&&endcap== 2 &&chamber== 8 &&layer== 4 )return true;
if(statringname.Index("ME41HV1")>=0&&endcap== 2 &&chamber== 8 &&layer== 6 )return true;
if(statringname.Index("ME41HV1")>=0&&endcap== 2 &&chamber== 10 &&layer== 1 )return true;
if(statringname.Index("ME41HV1")>=0&&endcap== 2 &&chamber== 10 &&layer== 2 )return true;
if(statringname.Index("ME41HV1")>=0&&endcap== 2 &&chamber== 10 &&layer== 3 )return true;
if(statringname.Index("ME41HV1")>=0&&endcap== 2 &&chamber== 10 &&layer== 4 )return true;
if(statringname.Index("ME41HV1")>=0&&endcap== 2 &&chamber== 10 &&layer== 6 )return true;
if(statringname.Index("ME41HV2")>=0&&endcap== 2 &&chamber== 8 &&layer== 2 )return true;
if(statringname.Index("ME41HV2")>=0&&endcap== 2 &&chamber== 8 &&layer== 4 )return true;
if(statringname.Index("ME41HV2")>=0&&endcap== 2 &&chamber== 8 &&layer== 5 )return true;
if(statringname.Index("ME41HV2")>=0&&endcap== 2 &&chamber== 8 &&layer== 6 )return true;
if(statringname.Index("ME41HV2")>=0&&endcap== 2 &&chamber== 10 &&layer== 2 )return true;
if(statringname.Index("ME41HV2")>=0&&endcap== 2 &&chamber== 10 &&layer== 3 )return true;
if(statringname.Index("ME41HV2")>=0&&endcap== 2 &&chamber== 10 &&layer== 4 )return true;
if(statringname.Index("ME41HV3")>=0&&endcap== 2 &&chamber== 8 &&layer== 1 )return true;
if(statringname.Index("ME41HV3")>=0&&endcap== 2 &&chamber== 8 &&layer== 2 )return true;
if(statringname.Index("ME41HV3")>=0&&endcap== 2 &&chamber== 8 &&layer== 3 )return true;
if(statringname.Index("ME41HV3")>=0&&endcap== 2 &&chamber== 8 &&layer== 5 )return true;
if(statringname.Index("ME41HV3")>=0&&endcap== 2 &&chamber== 8 &&layer== 6 )return true;
if(statringname.Index("ME41HV3")>=0&&endcap== 2 &&chamber== 10 &&layer== 2 )return true;
if(statringname.Index("ME41HV3")>=0&&endcap== 2 &&chamber== 10 &&layer== 3 )return true;
if(statringname.Index("ME41HV3")>=0&&endcap== 2 &&chamber== 10 &&layer== 4 )return true;
if(statringname.Index("ME41HV3")>=0&&endcap== 2 &&chamber== 10 &&layer== 5 )return true;
if(statringname.Index("ME41HV3")>=0&&endcap== 2 &&chamber== 10 &&layer== 6 )return true;
if(statringname.Index("ME32HV1")>=0&&endcap== 1 &&chamber== 24 &&layer== 1 )return true;
if(statringname.Index("ME32HV1")>=0&&endcap== 1 &&chamber== 24 &&layer== 2 )return true;
if(statringname.Index("ME32HV1")>=0&&endcap== 1 &&chamber== 24 &&layer== 3 )return true;
if(statringname.Index("ME32HV1")>=0&&endcap== 1 &&chamber== 24 &&layer== 5 )return true;
if(statringname.Index("ME32HV1")>=0&&endcap== 1 &&chamber== 24 &&layer== 6 )return true;
if(statringname.Index("ME32HV1")>=0&&endcap== 1 &&chamber== 25 &&layer== 1 )return true;
if(statringname.Index("ME32HV1")>=0&&endcap== 1 &&chamber== 25 &&layer== 2 )return true;
if(statringname.Index("ME32HV1")>=0&&endcap== 1 &&chamber== 25 &&layer== 3 )return true;
if(statringname.Index("ME32HV1")>=0&&endcap== 1 &&chamber== 25 &&layer== 4 )return true;
if(statringname.Index("ME32HV1")>=0&&endcap== 1 &&chamber== 25 &&layer== 6 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 1 &&chamber== 24 &&layer== 1 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 1 &&chamber== 24 &&layer== 2 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 1 &&chamber== 24 &&layer== 3 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 1 &&chamber== 24 &&layer== 4 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 1 &&chamber== 24 &&layer== 5 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 1 &&chamber== 24 &&layer== 6 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 1 &&chamber== 25 &&layer== 1 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 1 &&chamber== 25 &&layer== 2 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 1 &&chamber== 25 &&layer== 4 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 1 &&chamber== 25 &&layer== 5 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 1 &&chamber== 25 &&layer== 6 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 2 &&chamber== 16 &&layer== 4 )return true;
if(statringname.Index("ME32HV2")>=0&&endcap== 2 &&chamber== 25 &&layer== 4 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 24 &&layer== 1 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 24 &&layer== 2 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 24 &&layer== 3 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 24 &&layer== 4 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 24 &&layer== 5 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 24 &&layer== 6 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 25 &&layer== 1 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 25 &&layer== 2 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 25 &&layer== 3 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 25 &&layer== 4 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 25 &&layer== 5 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 1 &&chamber== 25 &&layer== 6 )return true;
if(statringname.Index("ME32HV3")>=0&&endcap== 2 &&chamber== 16 &&layer== 2 )return true;
if(statringname.Index("ME32HV4")>=0&&endcap== 1 &&chamber== 24 &&layer== 2 )return true;
if(statringname.Index("ME32HV4")>=0&&endcap== 1 &&chamber== 24 &&layer== 3 )return true;
if(statringname.Index("ME32HV4")>=0&&endcap== 1 &&chamber== 24 &&layer== 4 )return true;
if(statringname.Index("ME32HV4")>=0&&endcap== 1 &&chamber== 24 &&layer== 6 )return true;
if(statringname.Index("ME32HV4")>=0&&endcap== 1 &&chamber== 25 &&layer== 2 )return true;
if(statringname.Index("ME32HV4")>=0&&endcap== 1 &&chamber== 25 &&layer== 3 )return true;
if(statringname.Index("ME32HV4")>=0&&endcap== 1 &&chamber== 25 &&layer== 4 )return true;
if(statringname.Index("ME32HV4")>=0&&endcap== 1 &&chamber== 25 &&layer== 5 )return true;
if(statringname.Index("ME32HV4")>=0&&endcap== 1 &&chamber== 25 &&layer== 6 )return true;
if(statringname.Index("ME32HV4")>=0&&endcap== 2 &&chamber== 16 &&layer== 2 )return true;
if(statringname.Index("ME32HV5")>=0&&endcap== 1 &&chamber== 15 &&layer== 3 )return true;
if(statringname.Index("ME32HV5")>=0&&endcap== 1 &&chamber== 24 &&layer== 1 )return true;
if(statringname.Index("ME32HV5")>=0&&endcap== 1 &&chamber== 24 &&layer== 2 )return true;
if(statringname.Index("ME32HV5")>=0&&endcap== 1 &&chamber== 24 &&layer== 3 )return true;
if(statringname.Index("ME32HV5")>=0&&endcap== 1 &&chamber== 24 &&layer== 4 )return true;
if(statringname.Index("ME32HV5")>=0&&endcap== 1 &&chamber== 24 &&layer== 5 )return true;
if(statringname.Index("ME32HV5")>=0&&endcap== 1 &&chamber== 25 &&layer== 2 )return true;
if(statringname.Index("ME32HV5")>=0&&endcap== 1 &&chamber== 25 &&layer== 3 )return true;
if(statringname.Index("ME32HV5")>=0&&endcap== 1 &&chamber== 25 &&layer== 4 )return true;
if(statringname.Index("ME32HV5")>=0&&endcap== 1 &&chamber== 25 &&layer== 5 )return true;
if(statringname.Index("ME32HV5")>=0&&endcap== 2 &&chamber== 13 &&layer== 4 )return true;
if(statringname.Index("ME42HV1")>=0&&endcap== 2 &&chamber== 25 &&layer== 5 )return true;
if(statringname.Index("ME42HV3")>=0&&endcap== 2 &&chamber== 25 &&layer== 1 )return true;
if(statringname.Index("ME42HV4")>=0&&endcap== 2 &&chamber== 16 &&layer== 6 )return true;
return false;
}