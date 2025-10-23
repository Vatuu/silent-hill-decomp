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
            <td colspan=3 align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=matched_code_percent"/></a><br/><a href="https://decomp.dev/Vatuu/silent-hill-decomp"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&label=Silent+Hill+%28Fuzzy+Match%29&measure=fuzzy_match_percent"/></a></td>
        </tr>
        <tr>
            <th colspan=3>⚙ SLUS-00707 ⚙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=main"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&category=main&measure=fuzzy_match_percent"/></a></td>
            <td colspan=2>Main executable.</td>
        </tr>
        <tr>
            <th colspan=3>🧟‍♂️⚔⚙🎮 BODYPROG.BIN 🎮⚙⚔🧟‍♂️</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=engine"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&category=engine&measure=fuzzy_match_percent"/></a></td>
            <td colspan=2>Main game logic.</td>
        </tr>
        <tr>
            <th colspan=3>🎮 Game Screen Overlays 🎮</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=screen"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=screen&color=rgb(255,215,0)"/></a></td>
            <td colspan=2>Unique game screens.</td>
        </tr>
        <tr>
            <td colspan=3 align=center>
<details>
<summary>Click here to expand</summary>
<!-- Github incorrectly parses it if it's indented... -->
<table>
    <tbody>
        <tr>
          <th colspan=3>👨‍💼 B_KONAMI.BIN 👨‍💼</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Purpose</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=screen.b_konami"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=screen.b_konami&label=B_KONAMI&color=rgb(255,215,0)"/></a></td>
            <td>Boot screen logic.</td>
            <td><a href="https://github.com/Vatuu/silent-hill-decomp/commit/349b284d61a6901df3b96b99a612a66653d97238">First fully decompiled and matching overlay!</a></td>
        </tr>
        <tr>
          <th colspan=3>🎞 STREAM.BIN 🎞</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Purpose</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=screen.stream"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=screen.stream&label=STREAM&color=rgb(255,215,0)"/></a></td>
            <td>Full motion videos stream logic.</td>
            <td><a href="https://github.com/Vatuu/silent-hill-decomp/commit/d2541f2c10667860048a6bd17bc39bbd87280d47">Third fully decompiled and matching overlay!</a></td>
        </tr>
        <tr>
          <th colspan=3>💾 SAVELOAD.BIN 💾</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Purpose</td>
            <td>Note</td>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=screen.saveload"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=screen.saveload&label=SAVELOAD&color=rgb(255,215,0)"/></a></td>
            <td>Save and load screen logic.</td>
            <td><a href="https://github.com/Vatuu/silent-hill-decomp/commit/f72646453302f8c84933decf1326c9b9ebd3d622">Fourth fully decompiled and matching overlay!</a></td>
        </tr>
        <tr>
          <th colspan=3>📜 STF_ROLL.BIN 📜</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Purpose</td>
            <td>Note</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=screen.credits"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=screen.credits&label=CREDITS&color=rgb(255,215,0)"/></a></td>
            <td>Credits roll logic.</td>
            <td><a href="https://github.com/Vatuu/silent-hill-decomp/commit/701c1223daa79fa6317ee4d09d54ff3d99112abc">Second fully decompiled and matching overlay!</a></td>
        </tr>
        <tr>
          <th colspan=3>🛠 OPTION.BIN 🛠</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td>Purpose</td>
            <td>Note</td>
        </tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=screen.options"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=screen.options&label=OPTIONS&color=rgb(255,215,0)"/></a></td>
            <td>Options screen logic.</td>
            <td><a href="https://github.com/Vatuu/silent-hill-decomp/commit/a7ab294077dab8104a18ddacb8e567c23eaf0efe">Fifth fully decompiled and matching overlay!</a></td>
        </tr>
      </tbody>
    </table>
</details>
</td>
          <tr>
            <th colspan=3>🗺 Game Map Overlays 🗺</th>
          </tr>
          <tr>
            <td>Progress</td>
            <td colspan=2>Purpose</td>
          </tr>
          <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map"/></a></td>
            <td colspan=2>Map and character code.</td>
          </tr>
          <tr>
            <td colspan=3 align=center>
<details>
<summary>Click here to expand</summary>
<!-- Github incorrectly parses it if it's indented... -->
<table>
    <tbody>
        <tr>
          <th colspan=3>🏙 MAP0 🏙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map0_s00"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map0_s00&label=MAP0_S00"/></a></td>
            <td colspan=2>Old Silent Hill.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map0_s01"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map0_s01&label=MAP0_S01"/></a></td>
            <td colspan=2>Cafe in Old Silent Hill.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map0_s02"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map0_s02&label=MAP0_S02"/></a></td>
            <td colspan=2>Bonus unlockable areas in Old Silent Hill.</td>
        </tr>
        <tr>
          <th colspan=3>🏫 MAP1 🏫</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map1_s00"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map1_s00&label=MAP1_S00"/></a></td>
            <td colspan=2>School first floor, courtyard, and basement.</td>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map1_s01"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map1_s01&label=MAP1_S01"/></a></td>
            <td colspan=2>School second floor.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map1_s02"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map1_s02&label=MAP1_S02"/></a></td>
            <td colspan=2>School first floor and courtyard in Otherworld.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map1_s03"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map1_s03&label=MAP1_S03"/></a></td>
            <td colspan=2>School second floor and school roof in Otherworld.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map1_s04"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map1_s04&label=MAP1_S04&color=rgb(255,215,0)"/></a></td>
            <td>Unused <a href="https://github.com/Vatuu/silent-hill-decomp/issues/335#issuecomment-3393749791">(Click here for more information)</a></td>
			<td><a href="https://github.com/Vatuu/silent-hill-decomp/commit/c24f6f392e14eb4dbeac7fb0f0975f91a6539cb4">First fully decompiled and matching</br>map overlay!</a></td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map1_s05"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map1_s05&label=MAP1_S05"/></a></td>
            <td colspan=2>School boss fight.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map1_s06"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map1_s06&label=MAP1_S06"/></a></td>
            <td colspan=2>School first floor and basement after the boss fight.</td>
        </tr>
        <tr>
          <th colspan=3>🏙 MAP2 🏙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map2_s00"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map2_s00&label=MAP2_S00"/></a></td>
            <td colspan=2>Old Silent Hill.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map2_s01"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map2_s01&label=MAP2_S01&color=rgb(255,215,0)"/></a></td>
            <td>Church.</td>
			<td><a href="https://github.com/Vatuu/silent-hill-decomp/commit/5921aa73fb75645a75ae9c6fa0fdc30a0e4d58b2">Third fully decompiled and matching</br>map overlay!</a></td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map2_s02"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map2_s02&label=MAP2_S02"/></a></td>
            <td colspan=2>Central Silent Hill.</td>
        </tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map2_s03"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map2_s03&label=MAP2_S03&color=rgb(255,215,0)"/></a></td>
            <td>Unused <a href="https://github.com/Vatuu/silent-hill-decomp/issues/335#issuecomment-3393749791">(Click here for more information)</a></td>
			<td><a href="https://github.com/Vatuu/silent-hill-decomp/commit/bce45a64f45e2b561b4f0e675a7bda9bfe805dbf">Second fully decompiled and matching</br>map overlay!</a></td>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map2_s04"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map2_s04&label=MAP2_S04&color=rgb(255,215,0)"/></a></td>
            <td>Police station in Central Silent Hill.</td>
			<td><a href="https://github.com/Vatuu/silent-hill-decomp/commit/d7d655dfb59dc39328e7b14cae290b30ac0e992b">Fourth fully decompiled and matching</br>map overlay!</a></td>
        </tr>
        <tr>
          <th colspan=3>🏥 MAP3 🏥</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map3_s00"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map3_s00&label=MAP3_S00"/></a></td>
            <td colspan=2>Hospital beginning. Ends after meeting with Kaufmann.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map3_s01"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map3_s01&label=MAP3_S01"/></a></td>
            <td colspan=2>Hospital 1st and basement floors after meeting with Kaufmann.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map3_s02"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map3_s02&label=MAP3_S02"/></a></td>
            <td colspan=2>Green Lion Antique Shop cutscene in the Hospital.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map3_s03"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map3_s03&label=MAP3_S03"/></a></td>
            <td colspan=2>Hospital third and second floor in Otherworld.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map3_s04"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map3_s04&label=MAP3_S04"/></a></td>
            <td colspan=2>Hospital first floor in Otherworld.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map3_s05"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map3_s05&label=MAP3_S05"/></a></td>
            <td colspan=2>Hospital basement in Otherworld.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map3_s06"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map3_s06&label=MAP3_S06"/></a></td>
            <td colspan=2>Hospital first floor after the Otherworld section.</td>
        </tr>
        <tr>
          <th colspan=3>🏙 MAP4 🏙</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map4_s00"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map4_s00&label=MAP4_S00"/></a></td>
            <td colspan=2>Unused <a href="https://github.com/Vatuu/silent-hill-decomp/issues/335#issuecomment-3393749791">(Click here for more information)</a></td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map4_s01"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map4_s01&label=MAP4_S01"/></a></td>
            <td colspan=2>Green Lion Antique Shop in Central Silent Hill and Otherworld.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map4_s02"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map4_s02&label=MAP4_S02"/></a></td>
            <td colspan=2>Central Silent Hill in Otherworld.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map4_s03"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map4_s03&label=MAP4_S03"/></a></td>
            <td colspan=2>Mall and boss fight.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map4_s04"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map4_s04&label=MAP4_S04"/></a></td>
            <td>Hospital First Floor.</td>
            <td>Cutscene with Lisa after finding the<br/>altar in the Green Lion Antique Shop<br/>and meeting Lisa again after the mall<br/>boss fight.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map4_s05"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map4_s05&label=MAP4_S05"/></a></td>
            <td colspan=2>Central Silent Hill Floatstinger boss fight in Otherworld.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map4_s06"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map4_s06&label=MAP4_S06"/></a></td>
            <td colspan=2>Unused <a href="https://github.com/Vatuu/silent-hill-decomp/issues/335#issuecomment-3393749791">(Click here for more information)</a></td>
        </tr>
        <tr>
          <th colspan=3>🏙🍹 MAP5 🍹🏙</th>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map5_s00"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map5_s00&label=MAP5_S00"/></a></td>
            <td colspan=2>Sewers lower and upper levels.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map5_s01"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map5_s01&label=MAP5_S01"/></a></td>
            <td colspan=2>Silent Hill Resort Area.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map5_s02"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map5_s02&label=MAP5_S02"/></a></td>
            <td colspan=2>Annie's Bar and Indian Runner in Resort Area.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map5_s03"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map5_s03&label=MAP5_S03"/></a></td>
            <td colspan=2>Norman's Motel in Resort Area.</td>
        </tr>
        <tr>
          <th colspan=3>🏙🍹🔥 MAP6 🔥🍹🏙</th>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map6_s00"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map6_s00&label=MAP6_S00"/></a></td>
            <td colspan=2>Silent Hill Resort Area in Otherworld.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map6_s01"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map6_s01&label=MAP6_S01"/></a></td>
            <td colspan=2>Boat at Lakeside Pier.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map6_s02"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map6_s02&label=MAP6_S02"/></a></td>
            <td colspan=2>Lakeside Pier and Lighthouse.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map6_s03"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map6_s03&label=MAP6_S03"/></a></td>
            <td colspan=2>Sewer connecting to Lakeside Amusement Park.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map6_s04"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map6_s04&label=MAP6_S04"/></a></td>
            <td colspan=2>Cybil boss fight and cutscene of Dahlia kidnapping Alessa.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map6_s05"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&color=%23003cc7&measure=fuzzy_match&category=map.map6_s05&label=MAP6_S05"/></a></td>
            <td colspan=2>Unused <a href="https://github.com/Vatuu/silent-hill-decomp/issues/335#issuecomment-3393749791">(Click here for more information)</a></td>
        </tr>
        <tr>
          <th colspan=3>❔🏥 MAP7 🏥❔</th>
        </tr>
        <tr>
            <td>Progress</td>
            <td colspan=2>Location</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map7_s00"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map7_s00&label=MAP7_S00"/></a></td>
            <td colspan=2>Hospital first floor in Nowhere and Lisa cutscene.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map7_s01"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map7_s01&label=MAP7_S01"/></a></td>
            <td>Unknown</td>
            <td>Unknown parts of Nowhere.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map7_s02"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map7_s02&label=MAP7_S02"/></a></td>
            <td>Unknown</td>
            <td>Unknown parts of Nowhere, contains the<br/>cutscene where Alessa struggles against<br/>Dahlia.</td>
        </tr>
        <tr>
            <td align=center><a href="https://decomp.dev/Vatuu/silent-hill-decomp?category=map.map7_s03"><img src="https://decomp.dev/Vatuu/silent-hill-decomp.svg?mode=shield&measure=fuzzy_match&category=map.map7_s03&label=MAP7_S03"/></a></td>
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
- python3-venv
- bchunk
- 7z

Under a Debian-based distribution (or Windows with a Debian-based WSL2 setup), you can install these with the following commands:
```
sudo apt update
sudo apt install git build-essential binutils-mips-linux-gnu cpp-mips-linux-gnu python3 python3-venv bchunk p7zip-full
```

### Clone the repository
Clone `https://github.com/Vatuu/silent-hill-decomp` to your desired directory. Make sure to clone recursively!
```
git clone --recursive https://github.com/Vatuu/silent-hill-decomp.git && cd silent-hill-decomp
```

### Place the ROM
You will need to provide your own ROM dump of the NTSC-U 1.1 version of the game. If dumped correctly, you will have a `.BIN` file with the SHA1 hash `34278D31D9B9B12B3B5DB5E45BCBE548991ECBC7` (616,494,480 Bytes / 587 MiB).

After dumping, the `.BIN` file must be placed as `rom/image/SLUS-00707.bin` in the repo.

### Setup Python virtual environment and requirements
Modern Linux distros require a virtual environment to be set up before installing requirements with pip.

You can set up an environment in the repo folder with the following:
```bash
python3 -m venv .venv                      # Creates `.venv` folder with environment.
source .venv/bin/activate                  # Activates environment (must be run in every new terminal session).
python3 -m pip install -r requirements.txt # Installs project requirements from `requirements.txt`.
```

### Build the code
Run `make setup` to extract needed assets and code from the binary.
If the setup was successful, run `make` to build.
Once the build has finished, a folder named `build` will be produced. The output will be inside this.

Additional Make commands:
* `build`: Builds the executable and overlays.
* `check`: Builds the executable and overlays. After compilation, it compares checksums with the original files.
* `clean-build`: Renegerates the project configuration and builds the executable and overlays.
* `clean-check`: Renegerates the project configuration and builds the executable and overlays. After compilation, it compares checksums with the original files.
* `objdiff-config`: Generates project configuration for [Objdiff.](https://github.com/encounter/objdiff)
* `compilation-test`: Run progress and matching build processes for avoiding compilation errors.

NOTE: `clean-build/clean-check/compilation-test` is obligatory if the decompilation configuration files inside the `config` folder or the `Makefile` have been modified when intending to work on different overlays.

## Contributing
Contributions are welcome! Feel free to open a pull request. To help familiarize yourself with the decompilation workflow for *Silent Hill*, refer to our [Analysis Guide](https://github.com/Vatuu/silent-hill-decomp/blob/master/docs/Analysis%20Guide.md). For contributions to the repository, please follow our [Coding Conventions](https://github.com/Vatuu/silent-hill-decomp/blob/master/docs/Coding%20Conventions.md).

You can also reach out to us by opening an issue or joining the `#silent-hill` channel on the [PS1/PS2 Decompilation](https://discord.gg/VwCPdfbxgm) Discord server.

## Misc. Docs
* [Technical Game Information](https://github.com/Vatuu/silent-hill-decomp/blob/master/docs/Game%20Information.md)
* [Project File Organization](https://github.com/Vatuu/silent-hill-decomp/blob/master/docs/Organization.md)
