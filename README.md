# Silent Hill Decompilation Project

An in-progress decompilation of the 1.1 US release of Silent Hill on the Playstation 1.

## Progress
As commonly done on PlayStation 1 games, due limited memory of the platform, games' functionality was splitted among many `overlays`. Silent Hill is not the exception as it splits many of the specific screen related code part of the game and the most are level specific logic.

Progress bars powered by [decomp.dev](https://decomp.dev).

<table align=center>
    <tbody>
        <tr>
            <th colspan=3>⚙ SLUS-00707 ⚙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&category=main"/></td>
            <td colspan=2>Main Executable</td>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&category=sdk"/></td>
            <td colspan=2>Psy-Q Libraries</td>
        </tr>
        <tr>
            <th colspan=3>⚙ Game System Overlays ⚙</th>
        </tr>
        <tr>
            <td colspan=3 align=center>
<details>
<summary>Click here to expand</summary>
<!-- Github incorrectly parses it if it's indented... -->
<table>
    <tbody>
        <tr>
          <th colspan=3>🧟‍♂️⚔⚙🎮 BODYPROG.BIN 🎮⚙⚔🧟‍♂️</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&category=engine"/></td>
            <td colspan=2>Main Game Logic</td>
        </tr>
        <tr>
          <th colspan=3>👨‍💼 B_KONAMI.BIN 👨‍💼</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=screens/b_konami/b_konami"/></td>
            <td colspan=2>Boot Screen Logic</td>
        </tr>
        <tr>
          <th colspan=3>🎞 STREAM.BIN 🎞</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=screens/stream/stream&color=rgb(0,200,0)"/></td>
            <td>Full Motion Video Stream Logic</td>
        </tr>
        <tr>
          <th colspan=3>💾 SAVELOAD.BIN 💾</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=screens/saveload/saveload"/></td>
            <td colspan=2>Save and Load Screen Logic</td>
        </tr>
        <tr>
          <th colspan=3>📜 STF_ROLL.BIN 📜</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=screens/credits/credits"/></td>
            <td colspan=2>Credits Roll Logic</td>
        </tr>
        <tr>
          <th colspan=3>🛠 OPTION.BIN 🛠</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=screens/options/options"/></td>
            <td colspan=2>Options Screen Logic</td>
        </tr>
      </tbody>
    </table>
</details>
</td>
          <tr>
            <th colspan=3>🗺 Game Map Overlays 🗺</th>
          </tr>
          <tr>
            <td colspan=3 align=center>
<details>
<summary>Click here to expand</summary>
<!-- Github incorrectly parses it if it's indented... -->
<table>
    <tbody>
        <tr>
          <th colspan=3>🏙 MAP0_S00.BIN 🏙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map0_s00/map0_s00"/></td>
            <td colspan=2>Old Silent Hill</td>
        </tr>
        <tr>
          <th colspan=3>☕ MAP0_S01.BIN ☕</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map0_s01/map0_s01"/></td>
            <td colspan=2>Cafe 5to2 (Old Silent Hill)</td>
        </tr>
        <tr>
          <th colspan=3>🏙➕ MAP0_S02.BIN ➕🏙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map0_s02/map0_s02"/></td>
            <td colspan=2>Bonus Unlockable Areas (Old Silent Hill)</td>
        </tr>
        <tr>
          <th colspan=3>🏫 MAP1_S00.BIN 🏫</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map1_s00/map1_s00"/></td>
            <td colspan=2>School First Floor + Courtyard + Basement</td>
        </tr>
        <tr>
          <th colspan=3>🏫 MAP1_S01.BIN 🏫</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map1_s01/map1_s01"/></td>
            <td colspan=2>School Second Floor</td>
        </tr>
        <tr>
          <th colspan=3>🏫 MAP1_S02.BIN 🏫</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map1_s02/map1_s02"/></td>
            <td colspan=2>School First Floor + Courtyard (Otherworld)</td>
        </tr>
        <tr>
          <th colspan=3>🏫 MAP1_S03.BIN 🏫</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map1_s03/map1_s03"/></td>
            <td colspan=2>School Second Floor + School Roof (Otherworld)</td>
        </tr>
        <tr>
          <th colspan=3>🏫 MAP1_S04.BIN 🏫</th>
        </tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map1_s04/map1_s05"/></td>
            <td>Unknown</td>
            <td>School Location, likely from the otherworld</td>
        </tr>
          <th colspan=3>🏫 MAP1_S05.BIN 🏫</th>
        </tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map1_s05/map1_s05"/></td>
            <td>Unknown</td>
            <td>School Location, likely from the otherworld</td>
        </tr>
          <th colspan=3>🏫 MAP1_S06.BIN 🏫</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map1_s06/map1_s06"/></td>
            <td colspan=2>School First Floor + Basement (After Boss Fight)</td>
        </tr>
        <tr>
          <th colspan=3>🏙 MAP2_S00.BIN 🏙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map2_s00/map2_s00"/></td>
            <td colspan=2>Old Silent Hill (After finishing the School)</td>
        </tr>
        <tr>
          <th colspan=3>⛪ MAP2_S01.BIN ⛪</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map2_s01/map2_s01"/></td>
            <td colspan=2>Church</td>
        </tr>
        <tr>
          <th colspan=3>🏙 MAP2_S02.BIN 🏙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map2_s02/map2_s02"/></td>
            <td colspan=2>Central Silent Hill</td>
        </tr>
        <tr>
          <th colspan=3>❔ MAP2_S03.BIN ❔</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map2_s03/map2_s03"/></td>
            <td>Unknown</td>
            <td>Location related to Central Silent Hill</td>
        </tr>
        <tr>
          <th colspan=3>👮‍♂️ MAP2_S04.BIN 👮‍♂️</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map2_s04/map2_s04"/></td>
            <td colspan=2>Police Station (Central Silent Hill)</td>
        </tr>
        <tr>
          <th colspan=3>🏥 MAP3_S00.BIN 🏥</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map3_s00/map3_s00"/></td>
            <td>Unknown</td>
            <td>Hospital Location, possibly only covers the reception<br/>and the examination room, but not any of the rooms<br/>around it</td>
        </tr>
        <tr>
          <th colspan=3>🏥 MAP3_S01.BIN 🏥</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map3_s01/map3_s01"/></td>
            <td>Unknown</td>
            <td>Hospital Location, the rest of the first floor of the<br/>Hospital not covered by <code>MAP3_S00.BIN</code> and the basement</td>
        </tr>
        <tr>
          <th colspan=3>🏥 MAP3_S02.BIN 🏥</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map3_s02/map3_s02"/></td>
            <td>Unknown</td>
            <td>Hospital Location, the part when Harry is going<br/>through the elevator until it gets dark</td>
        </tr>
        <tr>
          <th colspan=3>🏥 MAP3_S03.BIN 🏥</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map3_s03/map3_s03"/></td>
            <td colspan=2>Hospital Third and Second Floor (Otherworld)</td>
        </tr>
        <tr>
          <th colspan=3>🏥 MAP3_S04.BIN 🏥</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map3_s04/map3_s04"/></td>
            <td colspan=2>Hospital First Floor (Otherworld)</td>
        </tr>
        <tr>
          <th colspan=3>🏥 MAP3_S05.BIN 🏥</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map3_s05/map3_s05"/></td>
            <td colspan=2>Hospital Basement (Otherworld)</td>
        </tr>
        <tr>
          <th colspan=3>🏥 MAP3_S06.BIN 🏥</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map3_s06/map3_s06"/></td>
            <td colspan=2>Hospital First Floor (After Otherworld section)</td>
        </tr>
        <tr>
          <th colspan=3>❔ MAP4_S00.BIN ❔</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map4_s00/map4_s00"/></td>
            <td colspan=2>Unknown</td>
        </tr>
        <tr>
          <th colspan=3>💍 MAP4_S01.BIN 💍</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map4_s01/map4_s01"/></td>
            <td colspan=2>Green Lion Antique Shop (Normal and Otherworld)</td>
        </tr>
        <tr>
          <th colspan=3>❔ MAP4_S02.BIN ❔</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map4_s02/map4_s02"/></td>
            <td>Unknown</td>
            <td>Likely one of the two parts where Harry goes through<br/>Central Silent Hill (Otherworld)</td>
        </tr>
        <tr>
          <th colspan=3>🛍 MAP4_S03.BIN 🛍</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map4_s03/map4_s03"/></td>
            <td colspan=2>Mall and Boss Fight</td>
        </tr>
        <tr>
          <th colspan=3>🏥 MAP4_S04.BIN 🏥</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map4_s04/map4_s04"/></td>
            <td>Hospital First Floor</td>
            <td>Cutscene with Lisa after finding an altar in Green Lion<br/>and meeting Lisa again after Mall Boss Fight</td>
        </tr>
        <tr>
          <th colspan=3>❔ MAP4_S05.BIN ❔</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map4_s05/map4_s05"/></td>
            <td>Unknown</td>
            <td>Likely one of the two parts where Harry goes through<br/>Central Silent Hill (Otherworld)</td>
        </tr>
        <tr>
          <th colspan=3>❔ MAP4_S06.BIN ❔</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map4_s06/map4_s06"/></td>
            <td colspan=2>Unknown</td>
        </tr>
        <tr>
          <th colspan=3>💧 MAP5_S00.BIN 💧</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map5_s00/map5_s00"/></td>
            <td colspan=2>Sewers (Low and High levels)</td>
        </tr>
        <tr>
          <th colspan=3>🏙🍹 MAP5_S01.BIN 🍹🏙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map5_s01/map5_s01"/></td>
            <td colspan=2>Silent Hill Resort Area</td>
        </tr>
        <tr>
          <th colspan=3>🍻🏪 MAP5_S02.BIN 🏪🍻</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Locations</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map5_s02/map5_s02"/></td>
            <td colspan=2>Annie's Bar and Indian Runner (Resort Area)</td>
        </tr>
        <tr>
          <th colspan=3>🏨 MAP5_S03.BIN 🏨</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map5_s03/map5_s03"/></td>
            <td colspan=2>Norman's Motel (Resort Area)</td>
        </tr>
        <tr>
          <th colspan=3>🏙🍹 MAP6_S00.BIN 🍹🏙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map6_s00/map6_s00"/></td>
            <td colspan=2>Silent Hill Resort Area (Otherworld)</td>
        </tr>
        <tr>
          <th colspan=3>🛥 MAP6_S01.BIN 🛥</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map6_s01/map6_s01"/></td>
            <td colspan=2>Boat (Lakeside Pier)</td>
        </tr>
        <tr>
          <th colspan=3>🌊 MAP6_S02.BIN 🌊</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map6_s02/map6_s02"/></td>
            <td colspan=2>Lakeside Pier</td>
        </tr>
        <tr>
          <th colspan=3>💧 MAP6_S03.BIN 💧</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map6_s03/map6_s03"/></td>
            <td colspan=2>Sewer (Connecting to Lakeside Amusement Park)</td>
        </tr>
        <tr>
          <th colspan=3>👮‍♀️🧙‍♀️ MAP6_S04.BIN 🧙‍♀️👮‍♀️</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map6_s04/map6_s04"/></td>
            <td colspan=2>Cybil Boss Fight and Dahlia kidnapping Alessa cutscene</td>
        </tr>
        <tr>
          <th colspan=3>❔ MAP6_S05.BIN ❔</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map6_s05/map6_s05"/></td>
            <td colspan=2>Unknown</td>
        </tr>
        <tr>
          <th colspan=3>🏥 MAP7_S00.BIN 🏥</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map7_s00/map7_s00"/></td>
            <td colspan=2>Hospital First Floor (Nowhere)</td>
        </tr>
        <tr>
          <th colspan=3>❔ MAP7_S01.BIN ❔</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map7_s01/map7_s01"/></td>
            <td>Unknown</td>
            <td>Nowever related</td>
        </tr>
        <tr>
          <th colspan=3>❔ MAP7_S02.BIN ❔</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Location</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map7_s02/map7_s02"/></td>
            <td>Unknown</td>
            <td>Nowhere is a really confusing part of the game, specially<br/>this overlay as it contain parts of the previous one, despite<br/>that this now contain references to the cutscene where<br/>Alessa struggle against Dahlia</td>
        </tr>
        <tr>
          <th colspan=3>👿 MAP7_S03.BIN 👿</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map7_s03/map7_s03"/></td>
            <td colspan=2>Final Boss Fight</td>
        </tr>
      </tbody>
    </table>
</details>
</td>
    </tbody>
</table>

## Building (Linux/Windows)

### Install build dependencies
The build process has the following package requirements:
- git
- build-essential
- binutils-mips-linux-gnu
- cpp-mips-linux-gnu
- python3
- bchunk
- 7z

Under a Debian-based distribution (or Windows with a Debian-based WSL2 setup), you can install these with the following commands:
```
sudo apt update
sudo apt install git build-essential binutils-mips-linux-gnu cpp-mips-linux-gnu python3 bchunk p7zip-full
```

### Clone the repository
Clone `https://github.com/Vatuu/silent-hill-decomp` to your desired directory. Make sure to clone recursively!
```
git clone --recursive https://github.com/Vatuu/silent-hill-decomp.git && cd silent-hill-decomp
```

### Install Python3 requirements
Run `pip3 install -r requirements.txt`

### Place the ROM
You will need to provide your own ROM dump of the game. The required version is Silent Hill NTSC-U 1.1.
If done correctly, you will end up with a .BIN and a .CUE file. These must be placed in the `rom/image` folder and renamed to SLUS-00707.bin/.cue, respectively.
SHA1 Hashes:
- .cue: `299D08DCB44E7516F394C3DD5BA40690AE33FD22` 84 Bytes
- .bin: `34278D31D9B9B12B3B5DB5E45BCBE548991ECBC7` 616,494,480 Bytes / 587 MiB

### Build the code
Run `make setup` to extract needed assets and code from the binary.
If the setup was successful, run `make` to build.
Once the build has finished, a folder named `build` will be produced. The output will be inside this.

Additional Make commands:
* `check`: Builds the executable and overlays. After compilation, it compares checksums with the original files.
* `build-c`: Clears the configuration of the project without deleting files.
* `build-C`: Clears the configuration of the project without deleting files. After compilation, it compares checksums with the original files.

NOTE: `build-c/build-C` are obligatory if the configuration in the `Makefile` has been modified when intending to work on different overlays.

## Contributing
Contributions are welcome. Following our [code conventions](https://github.com/Vatuu/silent-hill-decomp/blob/master/docs/Coding%20Conventions.md), feel free to contribute via a pull request or issue and join us on the [PS1/PS2 Decompilation](https://discord.gg/VwCPdfbxgm) Discord server in the `#silent-hill` channel.
