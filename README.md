# Silent Hill Decompilation Project

An in-progress decompilation of the 1.1 US release of *Silent Hill* on the Playstation 1.

## Progress
Due to the limited memory on the PlayStation 1, games often distribute their logic and functionality across different binary overlays. *Silent Hill* follows this approach by separating core engine code, screen-related code, and map stage event code into many distinct binaries. The main executable (`SLUS_007.07` on the 1.1 NTSC release) serves primarily as a memory handler.

Progress bars powered by [decomp.dev](https://decomp.dev)

<table align=center>
    <tbody>
        <tr>
            <th colspan=3>Total Progress</th>
        </tr>
        <tr>
            <td colspan=3 align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&category=all"/></td>
        </tr>
        <tr>
            <th colspan=3>⚙ SLUS-00707 ⚙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&category=main"/></td>
            <td colspan=2>Main executable.</td>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&category=sdk"/></td>
            <td colspan=2>Psy-Q libraries.</td>
        </tr>
        <tr>
            <th colspan=3>🎮 Game System Overlays 🎮</th>
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
            <td colspan=2>Main game logic.</td>
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
            <td colspan=2>Boot screen logic.</td>
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
            <td>Full motion videos stream logic.</td>
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
            <td colspan=2>Save and load screen logic.</td>
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
            <td colspan=2>Credits roll logic.</td>
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
            <td colspan=2>Options screen logic.</td>
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
            <td colspan=2>Old Silent Hill.</td>
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
            <td colspan=2>Cafe in Old Silent Hill.</td>
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
            <td colspan=2>Bonus unlockable areas in Old Silent Hill.</td>
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
            <td colspan=2>School first floor, courtyard, and basement.</td>
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
            <td colspan=2>School second floor.</td>
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
            <td colspan=2>School first floor and courtyard in Otherworld.</td>
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
            <td colspan=2>School second floor and school roof in Otherworld.</td>
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
            <td>School location, likely in Otherworld.</td>
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
            <td>School location, likely in Otherworld.</td>
        </tr>
          <th colspan=3>🏫 MAP1_S06.BIN 🏫</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=code&unit=maps/map1_s06/map1_s06"/></td>
            <td colspan=2>School first floor and basement after the boss fight.</td>
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
            <td colspan=2>Old Silent Hill after finishing the school.</td>
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
            <td>Location related to Central Silent Hill.</td>
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
            <td colspan=2>Police station in Central Silent Hill.</td>
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
            <td>Hospital, possibly only the reception<br/>and examination rooms but none of<br/>the rooms around them.</td>
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
            <td>Hospital, possibly the rest of the first floor<br/>not covered by <code>MAP3_S00.BIN</code><br/>and the basement.</td>
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
            <td>Hospital, the part when Harry goes<br/>in the elevator and it goes dark.</td>
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
            <td colspan=2>Hospital third and second floor in Otherworld.</td>
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
            <td colspan=2>Hospital first floor in Otherworld.</td>
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
            <td colspan=2>Hospital basement in Otherworld.</td>
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
            <td colspan=2>Hospital first floor after the Otherworld section.</td>
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
            <td colspan=2>Green Lion Antique Shop in Old Silent Hill and Otherworld.</td>
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
            <td>Possibly one of the two parts where<br/>Harry goes through Central Silent Hill<br/>in Otherworld.</td>
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
            <td colspan=2>Mall and boss fight.</td>
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
            <td>Cutscene with Lisa after finding the<br/>altar in the Green Lion Antique Shop and<br/>meeting Lisa again after the mall boss fight.</td>
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
            <td>Possibly one of the two parts when<br/>Harry goes through Central Silent Hill<br/>in Otherworld.</td>
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
            <td colspan=2>Sewers lower and upper levels.</td>
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
            <td colspan=2>Silent Hill Resort Area.</td>
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
            <td colspan=2>Annie's Bar and Indian Runner in Resort Area.</td>
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
            <td colspan=2>Norman's Motel in Resort Area.</td>
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
            <td colspan=2>Silent Hill Resort Area in Otherworld.</td>
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
            <td colspan=2>Boat at Lakeside Pier.</td>
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
            <td colspan=2>Sewer connecting to Lakeside Amusement Park.</td>
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
            <td colspan=2>Cybil boss fight and cutscene of Dahlia kidnapping Alessa.</td>
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
            <td colspan=2>Hospital first floor in Nowhere.</td>
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
            <td>Nowever related.</td>
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
            <td>Unknown parts of Nowhere and parts of the<br/>cutscene when Alessa struggles against<br/>Dahlia.</td>
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
            <td colspan=2>Final boss fight.</td>
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
* `build`: Builds the executable and overlays.
* `check`: Builds the executable and overlays. After compilation, it compares checksums with the original files.
* `clean-build`: Clears the project configuration without deleting files.
* `clean-check`: Clears the project configuration without deleting files. After compilation, it compares checksums with the original files.
* `objdiff-config`: Generates project configuration for [objdiff](https://github.com/encounter/objdiff.)

NOTE: `clean-build/clean-check` are obligatory if the configuration in the `Makefile` has been modified when intending to work on different overlays.

## Contributing
Contributions are welcome. Following our [code conventions](https://github.com/Vatuu/silent-hill-decomp/blob/master/docs/Coding%20Conventions.md), feel free to contribute via a pull request or issue and join us in the [PS1/PS2 Decompilation](https://discord.gg/VwCPdfbxgm) Discord server's `#silent-hill` channel.
