// TODO: Rename to `SfxId`. There's a name clash with an SFX struct.
typedef enum _Sfx
{
    Sfx_Base = 1280,              // Base SFX (not valid in itself).

    Sfx_StartGame = Sfx_Base + 1, // `SND/FIRST.VAB`

    Sfx_Unk1283 = Sfx_Base + 3,

    Sfx_Unk1286 = Sfx_Base + 6,

    Sfx_Unk1296 = Sfx_Base + 16,
    Sfx_Unk1297 = Sfx_Base + 17,

    Sfx_Denied  = Sfx_Base + 24, // `1ST/BASE.VAB` onward, but loaded out of order?
    Sfx_Back    = Sfx_Base + 25,
    Sfx_Cancel  = Sfx_Base + 26,
    Sfx_Confirm = Sfx_Base + 27, // TODO: Continue this pattern.

    Sfx_Unk1300 = Sfx_Base + 20,
    Sfx_Unk1301 = Sfx_Base + 21,
    Sfx_Unk1302 = Sfx_Base + 22,
    Sfx_Unk1303 = Sfx_Base + 23,

    Sfx_Unk1308 = 1308,
    Sfx_Unk1309 = 1309,
    Sfx_Unk1310 = 1310,

    Sfx_Stumble0 = 1314,

    Sfx_Unk1316     = 1316,
    Sfx_Unk1317     = 1317,
    Sfx_Unk1318     = 1318,
    Sfx_Unk1319     = 1319,
    Sfx_HeavyBreath = 1320,
    Sfx_Unk1321     = 1321,
    Sfx_Unk1322     = 1322,
    Sfx_Unk1323     = 1323,
    Sfx_Unk1324     = 1324,

    Sfx_Unk1326 = 1326,
    Sfx_Unk1327 = 1327,
    Sfx_Unk1328 = 1328,
    Sfx_Unk1329 = 1329,

    Sfx_Stumble1 = 1333,
    Sfx_DoorJammed = 1334,
    Sfx_Unk1335  = 1335,
    Sfx_Unk1336  = 1336,
    Sfx_Unk1337  = 1337,
    Sfx_Unk1338  = 1338,
    Sfx_Unk1339  = 1339,
    Sfx_Unk1340  = 1340,
    Sfx_Unk1341  = 1341,
    Sfx_DoorUnlocked = 1342,

    Sfx_Unk1343 = 1343,
    Sfx_DoorLocked = 1344,

    Sfx_Unk1349 = 1349,

    Sfx_Unk1351 = 1351,
    Sfx_Unk1352 = 1352,
    Sfx_Unk1353 = 1353,
    Sfx_Unk1354 = 1354,
    Sfx_Unk1355 = 1355,
    Sfx_Unk1356 = 1356,
    Sfx_Unk1357 = 1357,
    Sfx_Unk1358 = 1358,
    Sfx_Unk1359 = 1359,
    Sfx_Unk1360 = 1360,
    Sfx_Unk1361 = 1361,

    Sfx_Unk1363 = 1363,
    Sfx_Unk1364 = 1364,
    Sfx_Unk1365 = 1365,
    Sfx_Unk1366 = 1366,

    Sfx_Unk1368 = 1368,
    Sfx_Unk1369 = 1369,
    Sfx_Unk1370 = 1370,

    Sfx_Unk1373 = 1373,
    Sfx_Unk1374 = 1374,
    Sfx_Unk1375 = 1375,

    Sfx_Unk1385 = 1385,
    Sfx_Unk1386 = 1386,
    Sfx_Unk1387 = 1387,

    Sfx_Unk1391 = 1391,

    Sfx_Unk1396 = 1396,
    Sfx_Unk1397 = 1397,
    Sfx_Unk1398 = 1398,
    Sfx_Unk1399 = 1399,

    Sfx_Unk1416 = 1416,
    Sfx_Unk1417 = 1417,

    Sfx_Unk1418 = 1418,
    Sfx_Unk1419 = 1419,
    Sfx_Unk1420 = 1420,
    Sfx_Unk1421 = 1421,
    Sfx_Unk1422 = 1422,
    Sfx_Unk1423 = 1423,

    Sfx_Unk1430 = 1430,
    Sfx_Unk1431 = 1431,
    Sfx_Unk1432 = 1432,
    Sfx_Unk1433 = 1433,

    Sfx_Unk1435 = 1435,
    Sfx_Unk1436 = 1436,
    Sfx_Unk1437 = 1437,
    Sfx_Unk1438 = 1438, // } Piano keys.
    Sfx_Unk1439 = 1439, // }
    Sfx_Unk1440 = 1440, // }
    Sfx_Unk1441 = 1441, // }
    Sfx_Unk1442 = 1442, // }
    Sfx_Unk1443 = 1443, // }
    Sfx_Unk1444 = 1444, // }
    Sfx_Unk1445 = 1445, // }

    Sfx_Unk1446 = 1446,

    Sfx_Unk1448 = 1448,
    Sfx_Unk1449 = 1449,

    Sfx_Unk1454 = 1454,

    Sfx_Unk1456 = 1456,

    Sfx_Unk1458 = 1458,
    Sfx_Unk1459 = 1459,

    Sfx_Unk1464 = 1464,

    Sfx_Unk1467 = 1467,

    Sfx_Unk1477 = 1477,

    Sfx_Unk1479 = 1479,
    Sfx_Unk1480 = 1480,

    Sfx_Unk1486 = 1486,
    Sfx_Unk1487 = 1487,
    Sfx_Unk1488 = 1488,
    Sfx_Unk1489 = 1489,
    Sfx_Unk1490 = 1490,
    Sfx_Unk1491 = 1491,
    Sfx_Unk1492 = 1492,
    Sfx_Unk1493 = 1493,
    Sfx_Unk1494 = 1494,
    Sfx_Unk1495 = 1495,
    Sfx_Unk1496 = 1496,

    Sfx_Unk1497 = 1497,

    Sfx_Unk1501 = 1501,
    Sfx_Unk1502 = 1502,
    Sfx_Unk1503 = 1503,

    Sfx_Unk1504 = 1504,
    Sfx_Unk1505 = 1505,

    Sfx_Unk1521 = 1521,
    Sfx_Unk1522 = 1522,
    Sfx_Unk1523 = 1523,

    Sfx_Unk1525 = 1525,
    Sfx_Unk1526 = 1526,
    Sfx_Unk1527 = 1527,

    Sfx_Unk1529 = 1529,

    Sfx_Unk1538 = 1538,
    Sfx_Unk1539 = 1539,

    Sfx_Unk1541 = 1541, // Door jammed alt.

    Sfx_Unk1567 = 1567,

    Sfx_Unk1590 = 1590,

    Sfx_Unk1594 = 1594,

    Sfx_Unk1601 = 1601,
    Sfx_Unk1602 = 1602,

    Sfx_Unk1604 = 1604,
    Sfx_Unk1605 = 1605,
    Sfx_Unk1606 = 1606,
    Sfx_Unk1607 = 1607,

    Sfx_Unk1609 = 1609,
    Sfx_Unk1610 = 1610,
    Sfx_Unk1611 = 1611,

    Sfx_Unk1617 = 1617,

    Sfx_Unk1619 = 1619,

    Sfx_Unk1622 = 1622,

    Sfx_Unk1623 = 1623,

    Sfx_Unk1626 = 1626,
    Sfx_Unk1627 = 1627,
    Sfx_Unk1628 = 1628,
    Sfx_Unk1629 = 1629,

    Sfx_Unk1638 = 1638,
    Sfx_Unk1639 = 1639,
    Sfx_Unk1640 = 1640,

    Sfx_Unk1642 = 1642,
    Sfx_Unk1643 = 1643,
    Sfx_Unk1644 = 1644,
    Sfx_Unk1645 = 1645,

    Sfx_Unk1647 = 1647,
    Sfx_Unk1648 = 1648,
    Sfx_Unk1649 = 1649,
    Sfx_Unk1650 = 1650,

    Sfx_Unk1653 = 1653,
    Sfx_Unk1654 = 1654,
    Sfx_Unk1655 = 1655,
    Sfx_Unk1656 = 1656,
    Sfx_Unk1657 = 1657,
    Sfx_Unk1658 = 1658,

    Sfx_Unk1660 = 1660,
    Sfx_Unk1661 = 1661,

    Sfx_Unk1664 = 1664,
    Sfx_Unk1665 = 1665,
    Sfx_Unk1666 = 1666,

    Sfx_Unk1671 = 1671,
    Sfx_Unk1672 = 1672,
    Sfx_Unk1673 = 1673,
    Sfx_Unk1674 = 1674,
    Sfx_Unk1675 = 1675,

    Sfx_Unk1688 = 1688,
    Sfx_Unk1689 = 1689,
    Sfx_Unk1690 = 1690,

    Sfx_Unk1699 = 1699,

    Sfx_Unk1916 = 1916,

    Sfx_Unk4664 = 4664,

    Sfx_Unk4699 = 4699
} e_Sfx;
