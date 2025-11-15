// TODO: Rename to `SfxId`. There's a name clash with an SFX struct.
typedef enum _SfxId
{
    Sfx_Base = 1280,                  // Base SFX (not valid in itself).

    Sfx_MenuStartGame = Sfx_Base + 1, // `SND/FIRST.VAB`

    Sfx_Unk1283 = Sfx_Base + 3,

    Sfx_Unk1286 = Sfx_Base + 6,

    Sfx_Unk1296 = Sfx_Base + 16,
    Sfx_Unk1297 = Sfx_Base + 17,

    Sfx_Unk1300 = Sfx_Base + 20,
    Sfx_Unk1301 = Sfx_Base + 21,
    Sfx_Unk1302 = Sfx_Base + 22,
    Sfx_Unk1303 = Sfx_Base + 23,

    Sfx_MenuError        = Sfx_Base + 0x18, // 1304, `1ST/BASE.VAB` onward, but loaded out of order?
    Sfx_MenuMove         = Sfx_Base + 0x19, // 1305
    Sfx_MenuCancel       = Sfx_Base + 0x1A, // 1306
    Sfx_MenuConfirm      = Sfx_Base + 0x1B, // 1307
    Sfx_MenuMap          = Sfx_Base + 0x1C, // 1308
    Sfx_DoorOpen0        = Sfx_Base + 0x1D, // 1309
    Sfx_DoorClose0       = Sfx_Base + 0x1E, // 1310
    Sfx_FootstepConcrete = Sfx_Base + 0x1F, // 1311
    Sfx_FootstepGrass    = Sfx_Base + 0x20, // 1312
    Sfx_Unk1313          = 1313,
    Sfx_Stumble0         = Sfx_Base + 0x22, // 1314

    Sfx_Unk1316               = 1316,
    Sfx_Unk1317               = 1317,
    Sfx_Unk1318               = 1318,
    Sfx_Unk1319               = 1319,
    Sfx_HarryHeavyBreath      = Sfx_Base + 0x28, // 1320
    Sfx_RadioInterferenceLoop = Sfx_Base + 0x29, // 1321
    Sfx_RadioStaticLoop       = Sfx_Base + 0x2A, // 1322
    Sfx_Unk1323               = 1323,            // } Pair.
    Sfx_Unk1324               = 1324,            // }

    Sfx_Unk1326 = 1326,
    Sfx_Unk1327 = 1327,
    Sfx_Unk1328 = 1328,
    Sfx_Unk1329 = 1329,

    Sfx_Unk1330       = 1330,
    Sfx_Unk1331       = 1331,
    Sfx_FootstepMetal = Sfx_Base + 0x34, // 1332
    Sfx_Stumble1      = Sfx_Base + 0x35, // 1333
    Sfx_DoorJammed    = Sfx_Base + 0x36, // 1334
    Sfx_UseKey        = Sfx_Base + 0x37, // 1335
    Sfx_Unk1336       = 1336,            // } Pair.
    Sfx_Unk1337       = 1337,            // }
    Sfx_Unk1338       = 1338,            // } Pair.
    Sfx_Unk1339       = 1339,            // }
    Sfx_Unk1340       = 1340,            // } Pair.
    Sfx_Unk1341       = 1341,            // }
    Sfx_DoorUnlocked  = Sfx_Base + 0x3E, // 1342
    Sfx_Unk1343       = 1343,
    Sfx_DoorLocked    = Sfx_Base + 0x40, // 1344

    Sfx_Unk1346 = 1346,

    Sfx_Unk1349 = 1349,

    Sfx_Unk1351 = 1351, // } Pair.
    Sfx_Unk1352 = 1352, // }
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

    Sfx_Unk1384 = 1384,
    Sfx_Unk1385 = 1385,
    Sfx_Unk1386 = 1386,
    Sfx_Unk1387 = 1387,
    Sfx_Unk1388 = 1388,
    Sfx_Unk1389 = 1389,

    Sfx_Unk1390 = 1390,
    Sfx_Unk1391 = 1391,

    Sfx_Unk1393 = 1393,
    Sfx_Unk1394 = 1394,

    Sfx_Unk1396 = 1396, // } Pair.
    Sfx_Unk1397 = 1397, // }
    Sfx_Unk1398 = 1398, // } Pair.
    Sfx_Unk1399 = 1399, // }

    Sfx_Unk1405 = 1405,

    Sfx_Unk1416 = 1416,
    Sfx_Unk1417 = 1417,

    Sfx_Unk1418 = 1418,
    Sfx_Unk1419 = 1419,
    Sfx_Unk1420 = 1420,
    Sfx_Unk1421 = 1421,
    Sfx_Unk1422 = 1422,
    Sfx_Unk1423 = 1423,

    Sfx_Unk1430 = 1430,
    Sfx_Unk1431 = 1431, // } Pair.
    Sfx_Unk1432 = 1432, // }
    Sfx_Unk1433 = 1433,
    Sfx_Unk1434 = 1434,
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

    Sfx_Unk1451 = 1451,

    Sfx_Unk1454 = 1454,
    Sfx_Unk1455 = 1455,
    Sfx_Unk1456 = 1456,
    Sfx_Unk1457 = 1457,
    Sfx_Unk1458 = 1458, // } Pair.
    Sfx_Unk1459 = 1459, // }
    Sfx_Unk1460 = 1460,
    Sfx_Unk1461 = 1461,

    Sfx_Unk1464 = 1464,
    Sfx_Unk1465 = 1465,
    Sfx_Unk1466 = 1466,
    Sfx_Unk1467 = 1467,

    Sfx_Unk1477 = 1477,
    Sfx_Unk1478 = 1478,
    Sfx_Unk1479 = 1479,
    Sfx_Unk1480 = 1480,
    Sfx_Unk1481 = 1481,
    Sfx_Unk1482 = 1482,
    Sfx_Unk1483 = 1483,
    Sfx_Unk1484 = 1484,
    Sfx_Unk1485 = 1485,
    Sfx_Unk1486 = 1486,
    Sfx_Unk1487 = 1487,
    Sfx_Unk1488 = 1488,
    Sfx_Unk1489 = 1489,
    Sfx_Unk1490 = 1490, // } Pair.
    Sfx_Unk1491 = 1491, // }
    Sfx_Unk1492 = 1492,
    Sfx_Unk1493 = 1493,
    Sfx_Unk1494 = 1494,
    Sfx_Unk1495 = 1495,
    Sfx_Unk1496 = 1496,
    Sfx_Unk1497 = 1497,

    Sfx_Unk1501 = 1501,
    Sfx_Unk1502 = 1502,
    Sfx_Unk1503 = 1503,
    Sfx_Unk1504 = 1504, // } Pair.
    Sfx_Unk1505 = 1505, // }

    Sfx_Unk1520 = 1520,
    Sfx_Unk1521 = 1521,
    Sfx_Unk1522 = 1522,
    Sfx_Unk1523 = 1523,

    Sfx_Unk1525 = 1525,
    Sfx_Unk1526 = 1526,
    Sfx_Unk1527 = 1527,

    Sfx_Unk1529 = 1529,

    Sfx_Unk1531 = 1531,
    Sfx_Unk1532 = 1532,

    Sfx_Unk1535 = 1535,
    Sfx_Unk1536 = 1536,
    Sfx_Unk1537 = 1537,
    Sfx_Unk1538 = 1538,
    Sfx_Unk1539 = 1539,

    Sfx_Unk1541 = 1541, // Door jammed alt.

    Sfx_Unk1543 = 1543,

    Sfx_Unk1554 = 1554,

    Sfx_Unk1556 = 1556,
    Sfx_Unk1557 = 1557,

    Sfx_Unk1565 = 1565,

    Sfx_Unk1567 = 1567,

    Sfx_Unk1586 = 1586,
    Sfx_Unk1587 = 1587,

    Sfx_Unk1590 = 1590,
    Sfx_Unk1591 = 1591,
    Sfx_Unk1592 = 1592,
    Sfx_Unk1593 = 1593,
    Sfx_Unk1594 = 1594,
    Sfx_Unk1595 = 1595,
    Sfx_Unk1596 = 1596,
    Sfx_Unk1597 = 1597,
    Sfx_Unk1598 = 1598,

    Sfx_Unk1600 = 1600,
    Sfx_Unk1601 = 1601, // } Pair.
    Sfx_Unk1602 = 1602, // }

    Sfx_Unk1604 = 1604, // } Pair.
    Sfx_Unk1605 = 1605, // }
    Sfx_Unk1606 = 1606,
    Sfx_Unk1607 = 1607,
    Sfx_Unk1608 = 1608,
    Sfx_Unk1609 = 1609, // } Pair.
    Sfx_Unk1610 = 1610, // }
    Sfx_Unk1611 = 1611,
    Sfx_Unk1612 = 1612,
    Sfx_Unk1613 = 1613,

    Sfx_Unk1617 = 1617,

    Sfx_Unk1619 = 1619,

    Sfx_Unk1622 = 1622,
    Sfx_Unk1623 = 1623,
    Sfx_Unk1624 = 1624,
    Sfx_Unk1625 = 1625,
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

    Sfx_Unk1663 = 1663,
    Sfx_Unk1664 = 1664,
    Sfx_Unk1665 = 1665,
    Sfx_Unk1666 = 1666,

    Sfx_Unk1669 = 1669,

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

    Sfx_Unk4108 = 4108,

    Sfx_Unk4149 = 4149,
    Sfx_Unk4150 = 4150,

    Sfx_Unk4152 = 4152,

    Sfx_Unk4658 = 4658,

    Sfx_Unk4661 = 4661,

    Sfx_Unk4664 = 4664,

    Sfx_Unk4699 = 4699,

    Sfx_Hack = NO_VALUE, // @hack Force enum to be treated as `s32`.
} e_SfxId;
