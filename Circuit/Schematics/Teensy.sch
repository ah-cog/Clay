<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.2.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="14" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="57" name="tCAD" color="7" fill="1" visible="no" active="no"/>
<layer number="59" name="tCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="60" name="bCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="7" fill="1" visible="no" active="no"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Patch_Top" color="12" fill="4" visible="yes" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="yes" active="yes"/>
<layer number="103" name="tMap" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="16" fill="1" visible="yes" active="yes"/>
<layer number="105" name="tPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="106" name="bPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="107" name="Crop" color="7" fill="1" visible="yes" active="yes"/>
<layer number="108" name="fp8" color="7" fill="1" visible="yes" active="yes"/>
<layer number="109" name="fp9" color="7" fill="1" visible="yes" active="yes"/>
<layer number="110" name="fp0" color="7" fill="1" visible="yes" active="yes"/>
<layer number="111" name="LPC17xx" color="7" fill="1" visible="yes" active="yes"/>
<layer number="112" name="tSilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="113" name="IDFDebug" color="4" fill="1" visible="no" active="yes"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="yes" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="123" name="tTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="124" name="bTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="126" name="_bNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="127" name="_tValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="128" name="_bValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="129" name="Mask" color="7" fill="1" visible="no" active="yes"/>
<layer number="131" name="tAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="132" name="bAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="yes" active="yes"/>
<layer number="150" name="Notes" color="7" fill="1" visible="no" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="152" name="_bDocu" color="7" fill="1" visible="yes" active="yes"/>
<layer number="153" name="FabDoc1" color="7" fill="1" visible="no" active="yes"/>
<layer number="154" name="FabDoc2" color="7" fill="1" visible="no" active="yes"/>
<layer number="155" name="FabDoc3" color="7" fill="1" visible="no" active="yes"/>
<layer number="199" name="Contour" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="yes" active="yes"/>
<layer number="201" name="201bmp" color="2" fill="10" visible="yes" active="yes"/>
<layer number="202" name="202bmp" color="3" fill="10" visible="yes" active="yes"/>
<layer number="203" name="203bmp" color="4" fill="10" visible="yes" active="yes"/>
<layer number="204" name="204bmp" color="5" fill="10" visible="yes" active="yes"/>
<layer number="205" name="205bmp" color="6" fill="10" visible="yes" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="10" visible="yes" active="yes"/>
<layer number="207" name="207bmp" color="8" fill="10" visible="yes" active="yes"/>
<layer number="208" name="208bmp" color="9" fill="10" visible="yes" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="217" name="217bmp" color="18" fill="1" visible="no" active="no"/>
<layer number="218" name="218bmp" color="19" fill="1" visible="no" active="no"/>
<layer number="219" name="219bmp" color="20" fill="1" visible="no" active="no"/>
<layer number="220" name="220bmp" color="21" fill="1" visible="no" active="no"/>
<layer number="221" name="221bmp" color="22" fill="1" visible="no" active="no"/>
<layer number="222" name="222bmp" color="23" fill="1" visible="no" active="no"/>
<layer number="223" name="223bmp" color="24" fill="1" visible="no" active="no"/>
<layer number="224" name="224bmp" color="25" fill="1" visible="no" active="no"/>
<layer number="225" name="225bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="226" name="226bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="227" name="227bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="228" name="228bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="229" name="229bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="230" name="230bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="231" name="231bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="248" name="Housing" color="7" fill="1" visible="yes" active="yes"/>
<layer number="249" name="Edge" color="7" fill="1" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="3" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="no" active="no"/>
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
<layer number="255" name="routoute" color="7" fill="1" visible="no" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="SparkFun-Aesthetics">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find non-functional items- supply symbols, logos, notations, frame blocks, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="CREATIVE_COMMONS">
<text x="-20.32" y="5.08" size="1.778" layer="51" font="vector">Released under the Creative Commons Attribution Share-Alike 4.0 License</text>
<text x="0" y="2.54" size="1.778" layer="51" font="vector"> https://creativecommons.org/licenses/by-sa/4.0/</text>
<text x="11.43" y="0" size="1.778" layer="51" font="vector">Designed by:</text>
</package>
</packages>
<symbols>
<symbol name="DOCFIELD">
<wire x1="0" y1="0" x2="71.12" y2="0" width="0.254" layer="94"/>
<wire x1="101.6" y1="15.24" x2="87.63" y2="15.24" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.254" layer="94"/>
<wire x1="0" y1="5.08" x2="71.12" y2="5.08" width="0.254" layer="94"/>
<wire x1="0" y1="5.08" x2="0" y2="15.24" width="0.254" layer="94"/>
<wire x1="101.6" y1="15.24" x2="101.6" y2="5.08" width="0.254" layer="94"/>
<wire x1="71.12" y1="5.08" x2="71.12" y2="0" width="0.254" layer="94"/>
<wire x1="71.12" y1="5.08" x2="87.63" y2="5.08" width="0.254" layer="94"/>
<wire x1="71.12" y1="0" x2="101.6" y2="0" width="0.254" layer="94"/>
<wire x1="87.63" y1="15.24" x2="87.63" y2="5.08" width="0.254" layer="94"/>
<wire x1="87.63" y1="15.24" x2="0" y2="15.24" width="0.254" layer="94"/>
<wire x1="87.63" y1="5.08" x2="101.6" y2="5.08" width="0.254" layer="94"/>
<wire x1="101.6" y1="5.08" x2="101.6" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="15.24" x2="0" y2="22.86" width="0.254" layer="94"/>
<wire x1="101.6" y1="35.56" x2="0" y2="35.56" width="0.254" layer="94"/>
<wire x1="101.6" y1="35.56" x2="101.6" y2="22.86" width="0.254" layer="94"/>
<wire x1="0" y1="22.86" x2="101.6" y2="22.86" width="0.254" layer="94"/>
<wire x1="0" y1="22.86" x2="0" y2="35.56" width="0.254" layer="94"/>
<wire x1="101.6" y1="22.86" x2="101.6" y2="15.24" width="0.254" layer="94"/>
<text x="1.27" y="1.27" size="2.54" layer="94" font="vector">Date:</text>
<text x="12.7" y="1.27" size="2.54" layer="94" font="vector">&gt;LAST_DATE_TIME</text>
<text x="72.39" y="1.27" size="2.54" layer="94" font="vector">Sheet:</text>
<text x="86.36" y="1.27" size="2.54" layer="94" font="vector">&gt;SHEET</text>
<text x="88.9" y="11.43" size="2.54" layer="94" font="vector">REV:</text>
<text x="1.524" y="17.78" size="2.54" layer="94" font="vector">TITLE:</text>
<text x="15.494" y="17.78" size="2.7432" layer="94" font="vector">&gt;DRAWING_NAME</text>
<text x="2.54" y="31.75" size="1.9304" layer="94">Released under the Creative Commons</text>
<text x="2.54" y="27.94" size="1.9304" layer="94">Attribution Share-Alike 4.0 License</text>
<text x="2.54" y="24.13" size="1.9304" layer="94"> https://creativecommons.org/licenses/by-sa/4.0/</text>
<text x="1.27" y="11.43" size="2.54" layer="94">Design by:</text>
</symbol>
<symbol name="GND-ISO">
<description>Isolated ground</description>
<pin name="GND-ISO" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
<wire x1="-2.032" y1="0" x2="2.032" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-0.762" x2="1.27" y2="-0.762" width="0.254" layer="94"/>
<wire x1="-0.508" y1="-1.524" x2="0.508" y2="-1.524" width="0.254" layer="94"/>
<text x="2.54" y="0" size="1.778" layer="96">&gt;VALUE</text>
<wire x1="1.27" y1="2.032" x2="1.27" y2="0.508" width="0.254" layer="94"/>
</symbol>
<symbol name="FRAME_LEDGER">
<wire x1="0" y1="0" x2="0" y2="279.4" width="0.4064" layer="94"/>
<wire x1="0" y1="279.4" x2="431.8" y2="279.4" width="0.4064" layer="94"/>
<wire x1="431.8" y1="279.4" x2="431.8" y2="0" width="0.4064" layer="94"/>
<wire x1="431.8" y1="0" x2="0" y2="0" width="0.4064" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND-ISO" prefix="GND-ISO">
<description>Isolated ground</description>
<gates>
<gate name="G$1" symbol="GND-ISO" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="FRAME-LEDGER" prefix="FRAME">
<description>&lt;b&gt;Schematic Frame&lt;/b&gt;&lt;p&gt;
Standard 11x14 US Ledger frame</description>
<gates>
<gate name="G$1" symbol="FRAME_LEDGER" x="0" y="0"/>
<gate name="G$2" symbol="DOCFIELD" x="330.2" y="0" addlevel="must"/>
</gates>
<devices>
<device name="" package="CREATIVE_COMMONS">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Teensy_3_Series_Chip_v1.2">
<packages>
<package name="QFP50P1200X1200X160-64N">
<smd name="1" x="-5.715" y="3.7592" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="2" x="-5.715" y="3.2512" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="3" x="-5.715" y="2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="4" x="-5.715" y="2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="5" x="-5.715" y="1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="6" x="-5.715" y="1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="7" x="-5.715" y="0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="8" x="-5.715" y="0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="9" x="-5.715" y="-0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="10" x="-5.715" y="-0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="11" x="-5.715" y="-1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="12" x="-5.715" y="-1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="13" x="-5.715" y="-2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="14" x="-5.715" y="-2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="15" x="-5.715" y="-3.2512" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="16" x="-5.715" y="-3.7592" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="17" x="-3.7592" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="18" x="-3.2512" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="19" x="-2.7432" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="20" x="-2.2606" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="21" x="-1.7526" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="22" x="-1.2446" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="23" x="-0.762" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="24" x="-0.254" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="25" x="0.254" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="26" x="0.762" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="27" x="1.2446" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="28" x="1.7526" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="29" x="2.2606" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="30" x="2.7432" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="31" x="3.2512" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="32" x="3.7592" y="-5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="33" x="5.715" y="-3.7592" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="34" x="5.715" y="-3.2512" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="35" x="5.715" y="-2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="36" x="5.715" y="-2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="37" x="5.715" y="-1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="38" x="5.715" y="-1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="39" x="5.715" y="-0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="40" x="5.715" y="-0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="41" x="5.715" y="0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="42" x="5.715" y="0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="43" x="5.715" y="1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="44" x="5.715" y="1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="45" x="5.715" y="2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="46" x="5.715" y="2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="47" x="5.715" y="3.2512" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="48" x="5.715" y="3.7592" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="49" x="3.7592" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="50" x="3.2512" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="51" x="2.7432" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="52" x="2.2606" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="53" x="1.7526" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="54" x="1.2446" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="55" x="0.762" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="56" x="0.254" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="57" x="-0.254" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="58" x="-0.762" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="59" x="-1.2446" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="60" x="-1.7526" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="61" x="-2.2606" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="62" x="-2.7432" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="63" x="-3.2512" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="64" x="-3.7592" y="5.715" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<wire x1="-4.2164" y1="5.1054" x2="-5.1054" y2="5.1054" width="0.1524" layer="21"/>
<wire x1="5.1054" y1="4.2164" x2="5.1054" y2="5.1054" width="0.1524" layer="21"/>
<wire x1="4.2164" y1="-5.1054" x2="5.1054" y2="-5.1054" width="0.1524" layer="21"/>
<wire x1="-4.7752" y1="4.1402" x2="-4.1402" y2="4.7752" width="0.1524" layer="21"/>
<wire x1="-5.1054" y1="-5.1054" x2="-4.2164" y2="-5.1054" width="0.1524" layer="21"/>
<wire x1="5.1054" y1="-5.1054" x2="5.1054" y2="-4.2164" width="0.1524" layer="21"/>
<wire x1="5.1054" y1="5.1054" x2="4.2164" y2="5.1054" width="0.1524" layer="21"/>
<wire x1="-5.1054" y1="5.1054" x2="-5.1054" y2="4.2164" width="0.1524" layer="21"/>
<wire x1="-5.1054" y1="-4.2164" x2="-5.1054" y2="-5.1054" width="0.1524" layer="21"/>
<wire x1="3.6068" y1="5.1054" x2="3.8862" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="3.8862" y1="5.1054" x2="3.8862" y2="6.096" width="0.1524" layer="51"/>
<wire x1="3.8862" y1="6.096" x2="3.6068" y2="6.096" width="0.1524" layer="51"/>
<wire x1="3.6068" y1="6.096" x2="3.6068" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="3.1242" y1="5.1054" x2="3.3782" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="3.3782" y1="5.1054" x2="3.3782" y2="6.096" width="0.1524" layer="51"/>
<wire x1="3.3782" y1="6.096" x2="3.1242" y2="6.096" width="0.1524" layer="51"/>
<wire x1="3.1242" y1="6.096" x2="3.1242" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="2.6162" y1="5.1054" x2="2.8956" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="2.8956" y1="5.1054" x2="2.8956" y2="6.096" width="0.1524" layer="51"/>
<wire x1="2.8956" y1="6.096" x2="2.6162" y2="6.096" width="0.1524" layer="51"/>
<wire x1="2.6162" y1="6.096" x2="2.6162" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="2.1082" y1="5.1054" x2="2.3876" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="2.3876" y1="5.1054" x2="2.3876" y2="6.096" width="0.1524" layer="51"/>
<wire x1="2.3876" y1="6.096" x2="2.1082" y2="6.096" width="0.1524" layer="51"/>
<wire x1="2.1082" y1="6.096" x2="2.1082" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="1.6256" y1="5.1054" x2="1.8796" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="1.8796" y1="5.1054" x2="1.8796" y2="6.096" width="0.1524" layer="51"/>
<wire x1="1.8796" y1="6.096" x2="1.6256" y2="6.096" width="0.1524" layer="51"/>
<wire x1="1.6256" y1="6.096" x2="1.6256" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="1.1176" y1="5.1054" x2="1.397" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="1.397" y1="5.1054" x2="1.397" y2="6.096" width="0.1524" layer="51"/>
<wire x1="1.397" y1="6.096" x2="1.1176" y2="6.096" width="0.1524" layer="51"/>
<wire x1="1.1176" y1="6.096" x2="1.1176" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="0.6096" y1="5.1054" x2="0.889" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="0.889" y1="5.1054" x2="0.889" y2="6.096" width="0.1524" layer="51"/>
<wire x1="0.889" y1="6.096" x2="0.6096" y2="6.096" width="0.1524" layer="51"/>
<wire x1="0.6096" y1="6.096" x2="0.6096" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="0.127" y1="5.1054" x2="0.381" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="0.381" y1="5.1054" x2="0.381" y2="6.096" width="0.1524" layer="51"/>
<wire x1="0.381" y1="6.096" x2="0.127" y2="6.096" width="0.1524" layer="51"/>
<wire x1="0.127" y1="6.096" x2="0.127" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-0.381" y1="5.1054" x2="-0.127" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-0.127" y1="5.1054" x2="-0.127" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-0.127" y1="6.096" x2="-0.381" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-0.381" y1="6.096" x2="-0.381" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-0.889" y1="5.1054" x2="-0.6096" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-0.6096" y1="5.1054" x2="-0.6096" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-0.6096" y1="6.096" x2="-0.889" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-0.889" y1="6.096" x2="-0.889" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-1.397" y1="5.1054" x2="-1.1176" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-1.1176" y1="5.1054" x2="-1.1176" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-1.1176" y1="6.096" x2="-1.397" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-1.397" y1="6.096" x2="-1.397" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-1.8796" y1="5.1054" x2="-1.6256" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-1.6256" y1="5.1054" x2="-1.6256" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-1.6256" y1="6.096" x2="-1.8796" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-1.8796" y1="6.096" x2="-1.8796" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-2.3876" y1="5.1054" x2="-2.1082" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-2.1082" y1="5.1054" x2="-2.1082" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-2.1082" y1="6.096" x2="-2.3876" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-2.3876" y1="6.096" x2="-2.3876" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-2.8956" y1="5.1054" x2="-2.6162" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-2.6162" y1="5.1054" x2="-2.6162" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-2.6162" y1="6.096" x2="-2.8956" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-2.8956" y1="6.096" x2="-2.8956" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-3.3782" y1="5.1054" x2="-3.1242" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-3.1242" y1="5.1054" x2="-3.1242" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-3.1242" y1="6.096" x2="-3.3782" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-3.3782" y1="6.096" x2="-3.3782" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-3.8862" y1="5.1054" x2="-3.8354" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-3.8354" y1="5.1054" x2="-3.6068" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-3.6068" y1="5.1054" x2="-3.6068" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-3.6068" y1="6.096" x2="-3.8862" y2="6.096" width="0.1524" layer="51"/>
<wire x1="-3.8862" y1="6.096" x2="-3.8862" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="3.6068" x2="-5.1054" y2="3.8354" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="3.8354" x2="-5.1054" y2="3.8862" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="3.8862" x2="-6.096" y2="3.8862" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="3.8862" x2="-6.096" y2="3.6068" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="3.6068" x2="-5.1054" y2="3.6068" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="3.1242" x2="-5.1054" y2="3.3782" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="3.3782" x2="-6.096" y2="3.3782" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="3.3782" x2="-6.096" y2="3.1242" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="3.1242" x2="-5.1054" y2="3.1242" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="2.6162" x2="-5.1054" y2="2.8956" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="2.8956" x2="-6.096" y2="2.8956" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="2.8956" x2="-6.096" y2="2.6162" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="2.6162" x2="-5.1054" y2="2.6162" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="2.1082" x2="-5.1054" y2="2.3876" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="2.3876" x2="-6.096" y2="2.3876" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="2.3876" x2="-6.096" y2="2.1082" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="2.1082" x2="-5.1054" y2="2.1082" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="1.6256" x2="-5.1054" y2="1.8796" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="1.8796" x2="-6.096" y2="1.8796" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="1.8796" x2="-6.096" y2="1.6256" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="1.6256" x2="-5.1054" y2="1.6256" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="1.1176" x2="-5.1054" y2="1.397" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="1.397" x2="-6.096" y2="1.397" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="1.397" x2="-6.096" y2="1.1176" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="1.1176" x2="-5.1054" y2="1.1176" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="0.6096" x2="-5.1054" y2="0.889" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="0.889" x2="-6.096" y2="0.889" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="0.889" x2="-6.096" y2="0.6096" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="0.6096" x2="-5.1054" y2="0.6096" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="0.127" x2="-5.1054" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="0.381" x2="-6.096" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="0.381" x2="-6.096" y2="0.127" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="0.127" x2="-5.1054" y2="0.127" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-0.381" x2="-5.1054" y2="-0.127" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-0.127" x2="-6.096" y2="-0.127" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-0.127" x2="-6.096" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-0.381" x2="-5.1054" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-0.889" x2="-5.1054" y2="-0.6096" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-0.6096" x2="-6.096" y2="-0.6096" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-0.6096" x2="-6.096" y2="-0.889" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-0.889" x2="-5.1054" y2="-0.889" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-1.397" x2="-5.1054" y2="-1.1176" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-1.1176" x2="-6.096" y2="-1.1176" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-1.1176" x2="-6.096" y2="-1.397" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-1.397" x2="-5.1054" y2="-1.397" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-1.8796" x2="-5.1054" y2="-1.6256" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-1.6256" x2="-6.096" y2="-1.6256" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-1.6256" x2="-6.096" y2="-1.8796" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-1.8796" x2="-5.1054" y2="-1.8796" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-2.3876" x2="-5.1054" y2="-2.1082" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-2.1082" x2="-6.096" y2="-2.1082" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-2.1082" x2="-6.096" y2="-2.3876" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-2.3876" x2="-5.1054" y2="-2.3876" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-2.8956" x2="-5.1054" y2="-2.6162" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-2.6162" x2="-6.096" y2="-2.6162" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-2.6162" x2="-6.096" y2="-2.8956" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-2.8956" x2="-5.1054" y2="-2.8956" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-3.3782" x2="-5.1054" y2="-3.1242" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-3.1242" x2="-6.096" y2="-3.1242" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-3.1242" x2="-6.096" y2="-3.3782" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-3.3782" x2="-5.1054" y2="-3.3782" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-3.8862" x2="-5.1054" y2="-3.6068" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-3.6068" x2="-6.096" y2="-3.6068" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-3.6068" x2="-6.096" y2="-3.8862" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-3.8862" x2="-5.1054" y2="-3.8862" width="0.1524" layer="51"/>
<wire x1="-3.6068" y1="-5.1054" x2="-3.8862" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-3.8862" y1="-5.1054" x2="-3.8862" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-3.8862" y1="-6.096" x2="-3.6068" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-3.6068" y1="-6.096" x2="-3.6068" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-3.1242" y1="-5.1054" x2="-3.3782" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-3.3782" y1="-5.1054" x2="-3.3782" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-3.3782" y1="-6.096" x2="-3.1242" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-3.1242" y1="-6.096" x2="-3.1242" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-2.6162" y1="-5.1054" x2="-2.8956" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-2.8956" y1="-5.1054" x2="-2.8956" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-2.8956" y1="-6.096" x2="-2.6162" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-2.6162" y1="-6.096" x2="-2.6162" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-2.1082" y1="-5.1054" x2="-2.3876" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-2.3876" y1="-5.1054" x2="-2.3876" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-2.3876" y1="-6.096" x2="-2.1082" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-2.1082" y1="-6.096" x2="-2.1082" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-1.6256" y1="-5.1054" x2="-1.8796" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-1.8796" y1="-5.1054" x2="-1.8796" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-1.8796" y1="-6.096" x2="-1.6256" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-1.6256" y1="-6.096" x2="-1.6256" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-1.1176" y1="-5.1054" x2="-1.397" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-1.397" y1="-5.1054" x2="-1.397" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-1.397" y1="-6.096" x2="-1.1176" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-1.1176" y1="-6.096" x2="-1.1176" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-0.6096" y1="-5.1054" x2="-0.889" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-0.889" y1="-5.1054" x2="-0.889" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-0.889" y1="-6.096" x2="-0.6096" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-0.6096" y1="-6.096" x2="-0.6096" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-0.127" y1="-5.1054" x2="-0.381" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="-0.381" y1="-5.1054" x2="-0.381" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-0.381" y1="-6.096" x2="-0.127" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="-0.127" y1="-6.096" x2="-0.127" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="0.381" y1="-5.1054" x2="0.127" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="0.127" y1="-5.1054" x2="0.127" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="0.127" y1="-6.096" x2="0.381" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="0.381" y1="-6.096" x2="0.381" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="0.889" y1="-5.1054" x2="0.6096" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="0.6096" y1="-5.1054" x2="0.6096" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="0.6096" y1="-6.096" x2="0.889" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="0.889" y1="-6.096" x2="0.889" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="1.397" y1="-5.1054" x2="1.1176" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="1.1176" y1="-5.1054" x2="1.1176" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="1.1176" y1="-6.096" x2="1.397" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="1.397" y1="-6.096" x2="1.397" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="1.8796" y1="-5.1054" x2="1.6256" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="1.6256" y1="-5.1054" x2="1.6256" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="1.6256" y1="-6.096" x2="1.8796" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="1.8796" y1="-6.096" x2="1.8796" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="2.3876" y1="-5.1054" x2="2.1082" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="2.1082" y1="-5.1054" x2="2.1082" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="2.1082" y1="-6.096" x2="2.3876" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="2.3876" y1="-6.096" x2="2.3876" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="2.8956" y1="-5.1054" x2="2.6162" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="2.6162" y1="-5.1054" x2="2.6162" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="2.6162" y1="-6.096" x2="2.8956" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="2.8956" y1="-6.096" x2="2.8956" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="3.3782" y1="-5.1054" x2="3.1242" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="3.1242" y1="-5.1054" x2="3.1242" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="3.1242" y1="-6.096" x2="3.3782" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="3.3782" y1="-6.096" x2="3.3782" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="3.8862" y1="-5.1054" x2="3.6068" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="3.6068" y1="-5.1054" x2="3.6068" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="3.6068" y1="-6.096" x2="3.8862" y2="-6.096" width="0.1524" layer="51"/>
<wire x1="3.8862" y1="-6.096" x2="3.8862" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-3.6068" x2="5.1054" y2="-3.8862" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-3.8862" x2="6.096" y2="-3.8862" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-3.8862" x2="6.096" y2="-3.6068" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-3.6068" x2="5.1054" y2="-3.6068" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-3.1242" x2="5.1054" y2="-3.3782" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-3.3782" x2="6.096" y2="-3.3782" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-3.3782" x2="6.096" y2="-3.1242" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-3.1242" x2="5.1054" y2="-3.1242" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-2.6162" x2="5.1054" y2="-2.8956" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-2.8956" x2="6.096" y2="-2.8956" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-2.8956" x2="6.096" y2="-2.6162" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-2.6162" x2="5.1054" y2="-2.6162" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-2.1082" x2="5.1054" y2="-2.3876" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-2.3876" x2="6.096" y2="-2.3876" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-2.3876" x2="6.096" y2="-2.1082" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-2.1082" x2="5.1054" y2="-2.1082" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-1.6256" x2="5.1054" y2="-1.8796" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-1.8796" x2="6.096" y2="-1.8796" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-1.8796" x2="6.096" y2="-1.6256" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-1.6256" x2="5.1054" y2="-1.6256" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-1.1176" x2="5.1054" y2="-1.397" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-1.397" x2="6.096" y2="-1.397" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-1.397" x2="6.096" y2="-1.1176" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-1.1176" x2="5.1054" y2="-1.1176" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-0.6096" x2="5.1054" y2="-0.889" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-0.889" x2="6.096" y2="-0.889" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-0.889" x2="6.096" y2="-0.6096" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-0.6096" x2="5.1054" y2="-0.6096" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-0.127" x2="5.1054" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-0.381" x2="6.096" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-0.381" x2="6.096" y2="-0.127" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-0.127" x2="5.1054" y2="-0.127" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="0.381" x2="5.1054" y2="0.127" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="0.127" x2="6.096" y2="0.127" width="0.1524" layer="51"/>
<wire x1="6.096" y1="0.127" x2="6.096" y2="0.381" width="0.1524" layer="51"/>
<wire x1="6.096" y1="0.381" x2="5.1054" y2="0.381" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="0.889" x2="5.1054" y2="0.6096" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="0.6096" x2="6.096" y2="0.6096" width="0.1524" layer="51"/>
<wire x1="6.096" y1="0.6096" x2="6.096" y2="0.889" width="0.1524" layer="51"/>
<wire x1="6.096" y1="0.889" x2="5.1054" y2="0.889" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="1.397" x2="5.1054" y2="1.1176" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="1.1176" x2="6.096" y2="1.1176" width="0.1524" layer="51"/>
<wire x1="6.096" y1="1.1176" x2="6.096" y2="1.397" width="0.1524" layer="51"/>
<wire x1="6.096" y1="1.397" x2="5.1054" y2="1.397" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="1.8796" x2="5.1054" y2="1.6256" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="1.6256" x2="6.096" y2="1.6256" width="0.1524" layer="51"/>
<wire x1="6.096" y1="1.6256" x2="6.096" y2="1.8796" width="0.1524" layer="51"/>
<wire x1="6.096" y1="1.8796" x2="5.1054" y2="1.8796" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="2.3876" x2="5.1054" y2="2.1082" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="2.1082" x2="6.096" y2="2.1082" width="0.1524" layer="51"/>
<wire x1="6.096" y1="2.1082" x2="6.096" y2="2.3876" width="0.1524" layer="51"/>
<wire x1="6.096" y1="2.3876" x2="5.1054" y2="2.3876" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="2.8956" x2="5.1054" y2="2.6162" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="2.6162" x2="6.096" y2="2.6162" width="0.1524" layer="51"/>
<wire x1="6.096" y1="2.6162" x2="6.096" y2="2.8956" width="0.1524" layer="51"/>
<wire x1="6.096" y1="2.8956" x2="5.1054" y2="2.8956" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="3.3782" x2="5.1054" y2="3.1242" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="3.1242" x2="6.096" y2="3.1242" width="0.1524" layer="51"/>
<wire x1="6.096" y1="3.1242" x2="6.096" y2="3.3782" width="0.1524" layer="51"/>
<wire x1="6.096" y1="3.3782" x2="5.1054" y2="3.3782" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="3.8862" x2="5.1054" y2="3.6068" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="3.6068" x2="6.096" y2="3.6068" width="0.1524" layer="51"/>
<wire x1="6.096" y1="3.6068" x2="6.096" y2="3.8862" width="0.1524" layer="51"/>
<wire x1="6.096" y1="3.8862" x2="5.1054" y2="3.8862" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="3.8354" x2="-3.8354" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="-5.1054" x2="5.1054" y2="-5.1054" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="-5.1054" x2="5.1054" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="5.1054" y1="5.1054" x2="-5.1054" y2="5.1054" width="0.1524" layer="51"/>
<wire x1="-5.1054" y1="5.1054" x2="-5.1054" y2="-5.1054" width="0.1524" layer="51"/>
<text x="-2.1844" y="3.81" size="0.8128" layer="25" font="vector" ratio="15" rot="SR0">&gt;NAME</text>
<text x="-2.1844" y="-4.445" size="0.8128" layer="25" font="vector" ratio="15" rot="SR0">&gt;VALUE</text>
</package>
<package name="QFP50P900X900X160-48N">
<smd name="1" x="-4.2164" y="2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="2" x="-4.2164" y="2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="3" x="-4.2164" y="1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="4" x="-4.2164" y="1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="5" x="-4.2164" y="0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="6" x="-4.2164" y="0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="7" x="-4.2164" y="-0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="8" x="-4.2164" y="-0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="9" x="-4.2164" y="-1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="10" x="-4.2164" y="-1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="11" x="-4.2164" y="-2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="12" x="-4.2164" y="-2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="13" x="-2.7432" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="14" x="-2.2606" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="15" x="-1.7526" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="16" x="-1.2446" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="17" x="-0.762" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="18" x="-0.254" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="19" x="0.254" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="20" x="0.762" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="21" x="1.2446" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="22" x="1.7526" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="23" x="2.2606" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="24" x="2.7432" y="-4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="25" x="4.2164" y="-2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="26" x="4.2164" y="-2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="27" x="4.2164" y="-1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="28" x="4.2164" y="-1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="29" x="4.2164" y="-0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="30" x="4.2164" y="-0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="31" x="4.2164" y="0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="32" x="4.2164" y="0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="33" x="4.2164" y="1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="34" x="4.2164" y="1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="35" x="4.2164" y="2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="36" x="4.2164" y="2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="37" x="2.7432" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="38" x="2.2606" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="39" x="1.7526" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="40" x="1.2446" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="41" x="0.762" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="42" x="0.254" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="43" x="-0.254" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="44" x="-0.762" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="45" x="-1.2446" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="46" x="-1.7526" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="47" x="-2.2606" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="48" x="-2.7432" y="4.2164" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<wire x1="-3.2258" y1="3.6068" x2="-3.6068" y2="3.6068" width="0.1524" layer="21"/>
<wire x1="-3.1496" y1="2.7686" x2="-2.7686" y2="3.1496" width="0.1524" layer="21"/>
<wire x1="-3.6068" y1="-3.6068" x2="-3.2258" y2="-3.6068" width="0.1524" layer="21"/>
<wire x1="3.6068" y1="-3.6068" x2="3.6068" y2="-3.2258" width="0.1524" layer="21"/>
<wire x1="3.6068" y1="3.6068" x2="3.2258" y2="3.6068" width="0.1524" layer="21"/>
<wire x1="-3.6068" y1="3.6068" x2="-3.6068" y2="3.2258" width="0.1524" layer="21"/>
<wire x1="-3.6068" y1="-3.2258" x2="-3.6068" y2="-3.6068" width="0.1524" layer="21"/>
<wire x1="3.2258" y1="-3.6068" x2="3.6068" y2="-3.6068" width="0.1524" layer="21"/>
<wire x1="3.6068" y1="3.2258" x2="3.6068" y2="3.6068" width="0.1524" layer="21"/>
<wire x1="2.6162" y1="3.6068" x2="2.8956" y2="3.6068" width="0" layer="51"/>
<wire x1="2.8956" y1="3.6068" x2="2.8956" y2="4.5974" width="0" layer="51"/>
<wire x1="2.8956" y1="4.5974" x2="2.6162" y2="4.5974" width="0" layer="51"/>
<wire x1="2.6162" y1="4.5974" x2="2.6162" y2="3.6068" width="0" layer="51"/>
<wire x1="2.1082" y1="3.6068" x2="2.3876" y2="3.6068" width="0" layer="51"/>
<wire x1="2.3876" y1="3.6068" x2="2.3876" y2="4.5974" width="0" layer="51"/>
<wire x1="2.3876" y1="4.5974" x2="2.1082" y2="4.5974" width="0" layer="51"/>
<wire x1="2.1082" y1="4.5974" x2="2.1082" y2="3.6068" width="0" layer="51"/>
<wire x1="1.6256" y1="3.6068" x2="1.8796" y2="3.6068" width="0" layer="51"/>
<wire x1="1.8796" y1="3.6068" x2="1.8796" y2="4.5974" width="0" layer="51"/>
<wire x1="1.8796" y1="4.5974" x2="1.6256" y2="4.5974" width="0" layer="51"/>
<wire x1="1.6256" y1="4.5974" x2="1.6256" y2="3.6068" width="0" layer="51"/>
<wire x1="1.1176" y1="3.6068" x2="1.397" y2="3.6068" width="0" layer="51"/>
<wire x1="1.397" y1="3.6068" x2="1.397" y2="4.5974" width="0" layer="51"/>
<wire x1="1.397" y1="4.5974" x2="1.1176" y2="4.5974" width="0" layer="51"/>
<wire x1="1.1176" y1="4.5974" x2="1.1176" y2="3.6068" width="0" layer="51"/>
<wire x1="0.6096" y1="3.6068" x2="0.889" y2="3.6068" width="0" layer="51"/>
<wire x1="0.889" y1="3.6068" x2="0.889" y2="4.5974" width="0" layer="51"/>
<wire x1="0.889" y1="4.5974" x2="0.6096" y2="4.5974" width="0" layer="51"/>
<wire x1="0.6096" y1="4.5974" x2="0.6096" y2="3.6068" width="0" layer="51"/>
<wire x1="0.127" y1="3.6068" x2="0.381" y2="3.6068" width="0" layer="51"/>
<wire x1="0.381" y1="3.6068" x2="0.381" y2="4.5974" width="0" layer="51"/>
<wire x1="0.381" y1="4.5974" x2="0.127" y2="4.5974" width="0" layer="51"/>
<wire x1="0.127" y1="4.5974" x2="0.127" y2="3.6068" width="0" layer="51"/>
<wire x1="-0.381" y1="3.6068" x2="-0.127" y2="3.6068" width="0" layer="51"/>
<wire x1="-0.127" y1="3.6068" x2="-0.127" y2="4.5974" width="0" layer="51"/>
<wire x1="-0.127" y1="4.5974" x2="-0.381" y2="4.5974" width="0" layer="51"/>
<wire x1="-0.381" y1="4.5974" x2="-0.381" y2="3.6068" width="0" layer="51"/>
<wire x1="-0.889" y1="3.6068" x2="-0.6096" y2="3.6068" width="0" layer="51"/>
<wire x1="-0.6096" y1="3.6068" x2="-0.6096" y2="4.5974" width="0" layer="51"/>
<wire x1="-0.6096" y1="4.5974" x2="-0.889" y2="4.5974" width="0" layer="51"/>
<wire x1="-0.889" y1="4.5974" x2="-0.889" y2="3.6068" width="0" layer="51"/>
<wire x1="-1.397" y1="3.6068" x2="-1.1176" y2="3.6068" width="0" layer="51"/>
<wire x1="-1.1176" y1="3.6068" x2="-1.1176" y2="4.5974" width="0" layer="51"/>
<wire x1="-1.1176" y1="4.5974" x2="-1.397" y2="4.5974" width="0" layer="51"/>
<wire x1="-1.397" y1="4.5974" x2="-1.397" y2="3.6068" width="0" layer="51"/>
<wire x1="-1.8796" y1="3.6068" x2="-1.6256" y2="3.6068" width="0" layer="51"/>
<wire x1="-1.6256" y1="3.6068" x2="-1.6256" y2="4.5974" width="0" layer="51"/>
<wire x1="-1.6256" y1="4.5974" x2="-1.8796" y2="4.5974" width="0" layer="51"/>
<wire x1="-1.8796" y1="4.5974" x2="-1.8796" y2="3.6068" width="0" layer="51"/>
<wire x1="-2.3876" y1="3.6068" x2="-2.3368" y2="3.6068" width="0" layer="51"/>
<wire x1="-2.3368" y1="3.6068" x2="-2.1082" y2="3.6068" width="0" layer="51"/>
<wire x1="-2.1082" y1="3.6068" x2="-2.1082" y2="4.5974" width="0" layer="51"/>
<wire x1="-2.1082" y1="4.5974" x2="-2.3876" y2="4.5974" width="0" layer="51"/>
<wire x1="-2.3876" y1="4.5974" x2="-2.3876" y2="3.6068" width="0" layer="51"/>
<wire x1="-2.8956" y1="3.6068" x2="-2.6162" y2="3.6068" width="0" layer="51"/>
<wire x1="-2.6162" y1="3.6068" x2="-2.6162" y2="4.5974" width="0" layer="51"/>
<wire x1="-2.6162" y1="4.5974" x2="-2.8956" y2="4.5974" width="0" layer="51"/>
<wire x1="-2.8956" y1="4.5974" x2="-2.8956" y2="3.6068" width="0" layer="51"/>
<wire x1="-3.6068" y1="2.6162" x2="-3.6068" y2="2.8956" width="0" layer="51"/>
<wire x1="-3.6068" y1="2.8956" x2="-4.5974" y2="2.8956" width="0" layer="51"/>
<wire x1="-4.5974" y1="2.8956" x2="-4.5974" y2="2.6162" width="0" layer="51"/>
<wire x1="-4.5974" y1="2.6162" x2="-3.6068" y2="2.6162" width="0" layer="51"/>
<wire x1="-3.6068" y1="2.1082" x2="-3.6068" y2="2.3368" width="0" layer="51"/>
<wire x1="-3.6068" y1="2.3368" x2="-3.6068" y2="2.3876" width="0" layer="51"/>
<wire x1="-3.6068" y1="2.3876" x2="-4.5974" y2="2.3876" width="0" layer="51"/>
<wire x1="-4.5974" y1="2.3876" x2="-4.5974" y2="2.1082" width="0" layer="51"/>
<wire x1="-4.5974" y1="2.1082" x2="-3.6068" y2="2.1082" width="0" layer="51"/>
<wire x1="-3.6068" y1="1.6256" x2="-3.6068" y2="1.8796" width="0" layer="51"/>
<wire x1="-3.6068" y1="1.8796" x2="-4.5974" y2="1.8796" width="0" layer="51"/>
<wire x1="-4.5974" y1="1.8796" x2="-4.5974" y2="1.6256" width="0" layer="51"/>
<wire x1="-4.5974" y1="1.6256" x2="-3.6068" y2="1.6256" width="0" layer="51"/>
<wire x1="-3.6068" y1="1.1176" x2="-3.6068" y2="1.397" width="0" layer="51"/>
<wire x1="-3.6068" y1="1.397" x2="-4.5974" y2="1.397" width="0" layer="51"/>
<wire x1="-4.5974" y1="1.397" x2="-4.5974" y2="1.1176" width="0" layer="51"/>
<wire x1="-4.5974" y1="1.1176" x2="-3.6068" y2="1.1176" width="0" layer="51"/>
<wire x1="-3.6068" y1="0.6096" x2="-3.6068" y2="0.889" width="0" layer="51"/>
<wire x1="-3.6068" y1="0.889" x2="-4.5974" y2="0.889" width="0" layer="51"/>
<wire x1="-4.5974" y1="0.889" x2="-4.5974" y2="0.6096" width="0" layer="51"/>
<wire x1="-4.5974" y1="0.6096" x2="-3.6068" y2="0.6096" width="0" layer="51"/>
<wire x1="-3.6068" y1="0.127" x2="-3.6068" y2="0.381" width="0" layer="51"/>
<wire x1="-3.6068" y1="0.381" x2="-4.5974" y2="0.381" width="0" layer="51"/>
<wire x1="-4.5974" y1="0.381" x2="-4.5974" y2="0.127" width="0" layer="51"/>
<wire x1="-4.5974" y1="0.127" x2="-3.6068" y2="0.127" width="0" layer="51"/>
<wire x1="-3.6068" y1="-0.381" x2="-3.6068" y2="-0.127" width="0" layer="51"/>
<wire x1="-3.6068" y1="-0.127" x2="-4.5974" y2="-0.127" width="0" layer="51"/>
<wire x1="-4.5974" y1="-0.127" x2="-4.5974" y2="-0.381" width="0" layer="51"/>
<wire x1="-4.5974" y1="-0.381" x2="-3.6068" y2="-0.381" width="0" layer="51"/>
<wire x1="-3.6068" y1="-0.889" x2="-3.6068" y2="-0.6096" width="0" layer="51"/>
<wire x1="-3.6068" y1="-0.6096" x2="-4.5974" y2="-0.6096" width="0" layer="51"/>
<wire x1="-4.5974" y1="-0.6096" x2="-4.5974" y2="-0.889" width="0" layer="51"/>
<wire x1="-4.5974" y1="-0.889" x2="-3.6068" y2="-0.889" width="0" layer="51"/>
<wire x1="-3.6068" y1="-1.397" x2="-3.6068" y2="-1.1176" width="0" layer="51"/>
<wire x1="-3.6068" y1="-1.1176" x2="-4.5974" y2="-1.1176" width="0" layer="51"/>
<wire x1="-4.5974" y1="-1.1176" x2="-4.5974" y2="-1.397" width="0" layer="51"/>
<wire x1="-4.5974" y1="-1.397" x2="-3.6068" y2="-1.397" width="0" layer="51"/>
<wire x1="-3.6068" y1="-1.8796" x2="-3.6068" y2="-1.6256" width="0" layer="51"/>
<wire x1="-3.6068" y1="-1.6256" x2="-4.5974" y2="-1.6256" width="0" layer="51"/>
<wire x1="-4.5974" y1="-1.6256" x2="-4.5974" y2="-1.8796" width="0" layer="51"/>
<wire x1="-4.5974" y1="-1.8796" x2="-3.6068" y2="-1.8796" width="0" layer="51"/>
<wire x1="-3.6068" y1="-2.3876" x2="-3.6068" y2="-2.1082" width="0" layer="51"/>
<wire x1="-3.6068" y1="-2.1082" x2="-4.5974" y2="-2.1082" width="0" layer="51"/>
<wire x1="-4.5974" y1="-2.1082" x2="-4.5974" y2="-2.3876" width="0" layer="51"/>
<wire x1="-4.5974" y1="-2.3876" x2="-3.6068" y2="-2.3876" width="0" layer="51"/>
<wire x1="-3.6068" y1="-2.8956" x2="-3.6068" y2="-2.6162" width="0" layer="51"/>
<wire x1="-3.6068" y1="-2.6162" x2="-4.5974" y2="-2.6162" width="0" layer="51"/>
<wire x1="-4.5974" y1="-2.6162" x2="-4.5974" y2="-2.8956" width="0" layer="51"/>
<wire x1="-4.5974" y1="-2.8956" x2="-3.6068" y2="-2.8956" width="0" layer="51"/>
<wire x1="-2.6162" y1="-3.6068" x2="-2.8956" y2="-3.6068" width="0" layer="51"/>
<wire x1="-2.8956" y1="-3.6068" x2="-2.8956" y2="-4.5974" width="0" layer="51"/>
<wire x1="-2.8956" y1="-4.5974" x2="-2.6162" y2="-4.5974" width="0" layer="51"/>
<wire x1="-2.6162" y1="-4.5974" x2="-2.6162" y2="-3.6068" width="0" layer="51"/>
<wire x1="-2.1082" y1="-3.6068" x2="-2.3876" y2="-3.6068" width="0" layer="51"/>
<wire x1="-2.3876" y1="-3.6068" x2="-2.3876" y2="-4.5974" width="0" layer="51"/>
<wire x1="-2.3876" y1="-4.5974" x2="-2.1082" y2="-4.5974" width="0" layer="51"/>
<wire x1="-2.1082" y1="-4.5974" x2="-2.1082" y2="-3.6068" width="0" layer="51"/>
<wire x1="-1.6256" y1="-3.6068" x2="-1.8796" y2="-3.6068" width="0" layer="51"/>
<wire x1="-1.8796" y1="-3.6068" x2="-1.8796" y2="-4.5974" width="0" layer="51"/>
<wire x1="-1.8796" y1="-4.5974" x2="-1.6256" y2="-4.5974" width="0" layer="51"/>
<wire x1="-1.6256" y1="-4.5974" x2="-1.6256" y2="-3.6068" width="0" layer="51"/>
<wire x1="-1.1176" y1="-3.6068" x2="-1.397" y2="-3.6068" width="0" layer="51"/>
<wire x1="-1.397" y1="-3.6068" x2="-1.397" y2="-4.5974" width="0" layer="51"/>
<wire x1="-1.397" y1="-4.5974" x2="-1.1176" y2="-4.5974" width="0" layer="51"/>
<wire x1="-1.1176" y1="-4.5974" x2="-1.1176" y2="-3.6068" width="0" layer="51"/>
<wire x1="-0.6096" y1="-3.6068" x2="-0.889" y2="-3.6068" width="0" layer="51"/>
<wire x1="-0.889" y1="-3.6068" x2="-0.889" y2="-4.5974" width="0" layer="51"/>
<wire x1="-0.889" y1="-4.5974" x2="-0.6096" y2="-4.5974" width="0" layer="51"/>
<wire x1="-0.6096" y1="-4.5974" x2="-0.6096" y2="-3.6068" width="0" layer="51"/>
<wire x1="-0.127" y1="-3.6068" x2="-0.381" y2="-3.6068" width="0" layer="51"/>
<wire x1="-0.381" y1="-3.6068" x2="-0.381" y2="-4.5974" width="0" layer="51"/>
<wire x1="-0.381" y1="-4.5974" x2="-0.127" y2="-4.5974" width="0" layer="51"/>
<wire x1="-0.127" y1="-4.5974" x2="-0.127" y2="-3.6068" width="0" layer="51"/>
<wire x1="0.381" y1="-3.6068" x2="0.127" y2="-3.6068" width="0" layer="51"/>
<wire x1="0.127" y1="-3.6068" x2="0.127" y2="-4.5974" width="0" layer="51"/>
<wire x1="0.127" y1="-4.5974" x2="0.381" y2="-4.5974" width="0" layer="51"/>
<wire x1="0.381" y1="-4.5974" x2="0.381" y2="-3.6068" width="0" layer="51"/>
<wire x1="0.889" y1="-3.6068" x2="0.6096" y2="-3.6068" width="0" layer="51"/>
<wire x1="0.6096" y1="-3.6068" x2="0.6096" y2="-4.5974" width="0" layer="51"/>
<wire x1="0.6096" y1="-4.5974" x2="0.889" y2="-4.5974" width="0" layer="51"/>
<wire x1="0.889" y1="-4.5974" x2="0.889" y2="-3.6068" width="0" layer="51"/>
<wire x1="1.397" y1="-3.6068" x2="1.1176" y2="-3.6068" width="0" layer="51"/>
<wire x1="1.1176" y1="-3.6068" x2="1.1176" y2="-4.5974" width="0" layer="51"/>
<wire x1="1.1176" y1="-4.5974" x2="1.397" y2="-4.5974" width="0" layer="51"/>
<wire x1="1.397" y1="-4.5974" x2="1.397" y2="-3.6068" width="0" layer="51"/>
<wire x1="1.8796" y1="-3.6068" x2="1.6256" y2="-3.6068" width="0" layer="51"/>
<wire x1="1.6256" y1="-3.6068" x2="1.6256" y2="-4.5974" width="0" layer="51"/>
<wire x1="1.6256" y1="-4.5974" x2="1.8796" y2="-4.5974" width="0" layer="51"/>
<wire x1="1.8796" y1="-4.5974" x2="1.8796" y2="-3.6068" width="0" layer="51"/>
<wire x1="2.3876" y1="-3.6068" x2="2.1082" y2="-3.6068" width="0" layer="51"/>
<wire x1="2.1082" y1="-3.6068" x2="2.1082" y2="-4.5974" width="0" layer="51"/>
<wire x1="2.1082" y1="-4.5974" x2="2.3876" y2="-4.5974" width="0" layer="51"/>
<wire x1="2.3876" y1="-4.5974" x2="2.3876" y2="-3.6068" width="0" layer="51"/>
<wire x1="2.8956" y1="-3.6068" x2="2.6162" y2="-3.6068" width="0" layer="51"/>
<wire x1="2.6162" y1="-3.6068" x2="2.6162" y2="-4.5974" width="0" layer="51"/>
<wire x1="2.6162" y1="-4.5974" x2="2.8956" y2="-4.5974" width="0" layer="51"/>
<wire x1="2.8956" y1="-4.5974" x2="2.8956" y2="-3.6068" width="0" layer="51"/>
<wire x1="3.6068" y1="-2.6162" x2="3.6068" y2="-2.8956" width="0" layer="51"/>
<wire x1="3.6068" y1="-2.8956" x2="4.5974" y2="-2.8956" width="0" layer="51"/>
<wire x1="4.5974" y1="-2.8956" x2="4.5974" y2="-2.6162" width="0" layer="51"/>
<wire x1="4.5974" y1="-2.6162" x2="3.6068" y2="-2.6162" width="0" layer="51"/>
<wire x1="3.6068" y1="-2.1082" x2="3.6068" y2="-2.3876" width="0" layer="51"/>
<wire x1="3.6068" y1="-2.3876" x2="4.5974" y2="-2.3876" width="0" layer="51"/>
<wire x1="4.5974" y1="-2.3876" x2="4.5974" y2="-2.1082" width="0" layer="51"/>
<wire x1="4.5974" y1="-2.1082" x2="3.6068" y2="-2.1082" width="0" layer="51"/>
<wire x1="3.6068" y1="-1.6256" x2="3.6068" y2="-1.8796" width="0" layer="51"/>
<wire x1="3.6068" y1="-1.8796" x2="4.5974" y2="-1.8796" width="0" layer="51"/>
<wire x1="4.5974" y1="-1.8796" x2="4.5974" y2="-1.6256" width="0" layer="51"/>
<wire x1="4.5974" y1="-1.6256" x2="3.6068" y2="-1.6256" width="0" layer="51"/>
<wire x1="3.6068" y1="-1.1176" x2="3.6068" y2="-1.397" width="0" layer="51"/>
<wire x1="3.6068" y1="-1.397" x2="4.5974" y2="-1.397" width="0" layer="51"/>
<wire x1="4.5974" y1="-1.397" x2="4.5974" y2="-1.1176" width="0" layer="51"/>
<wire x1="4.5974" y1="-1.1176" x2="3.6068" y2="-1.1176" width="0" layer="51"/>
<wire x1="3.6068" y1="-0.6096" x2="3.6068" y2="-0.889" width="0" layer="51"/>
<wire x1="3.6068" y1="-0.889" x2="4.5974" y2="-0.889" width="0" layer="51"/>
<wire x1="4.5974" y1="-0.889" x2="4.5974" y2="-0.6096" width="0" layer="51"/>
<wire x1="4.5974" y1="-0.6096" x2="3.6068" y2="-0.6096" width="0" layer="51"/>
<wire x1="3.6068" y1="-0.127" x2="3.6068" y2="-0.381" width="0" layer="51"/>
<wire x1="3.6068" y1="-0.381" x2="4.5974" y2="-0.381" width="0" layer="51"/>
<wire x1="4.5974" y1="-0.381" x2="4.5974" y2="-0.127" width="0" layer="51"/>
<wire x1="4.5974" y1="-0.127" x2="3.6068" y2="-0.127" width="0" layer="51"/>
<wire x1="3.6068" y1="0.381" x2="3.6068" y2="0.127" width="0" layer="51"/>
<wire x1="3.6068" y1="0.127" x2="4.5974" y2="0.127" width="0" layer="51"/>
<wire x1="4.5974" y1="0.127" x2="4.5974" y2="0.381" width="0" layer="51"/>
<wire x1="4.5974" y1="0.381" x2="3.6068" y2="0.381" width="0" layer="51"/>
<wire x1="3.6068" y1="0.889" x2="3.6068" y2="0.6096" width="0" layer="51"/>
<wire x1="3.6068" y1="0.6096" x2="4.5974" y2="0.6096" width="0" layer="51"/>
<wire x1="4.5974" y1="0.6096" x2="4.5974" y2="0.889" width="0" layer="51"/>
<wire x1="4.5974" y1="0.889" x2="3.6068" y2="0.889" width="0" layer="51"/>
<wire x1="3.6068" y1="1.397" x2="3.6068" y2="1.1176" width="0" layer="51"/>
<wire x1="3.6068" y1="1.1176" x2="4.5974" y2="1.1176" width="0" layer="51"/>
<wire x1="4.5974" y1="1.1176" x2="4.5974" y2="1.397" width="0" layer="51"/>
<wire x1="4.5974" y1="1.397" x2="3.6068" y2="1.397" width="0" layer="51"/>
<wire x1="3.6068" y1="1.8796" x2="3.6068" y2="1.6256" width="0" layer="51"/>
<wire x1="3.6068" y1="1.6256" x2="4.5974" y2="1.6256" width="0" layer="51"/>
<wire x1="4.5974" y1="1.6256" x2="4.5974" y2="1.8796" width="0" layer="51"/>
<wire x1="4.5974" y1="1.8796" x2="3.6068" y2="1.8796" width="0" layer="51"/>
<wire x1="3.6068" y1="2.3876" x2="3.6068" y2="2.1082" width="0" layer="51"/>
<wire x1="3.6068" y1="2.1082" x2="4.5974" y2="2.1082" width="0" layer="51"/>
<wire x1="4.5974" y1="2.1082" x2="4.5974" y2="2.3876" width="0" layer="51"/>
<wire x1="4.5974" y1="2.3876" x2="3.6068" y2="2.3876" width="0" layer="51"/>
<wire x1="3.6068" y1="2.8956" x2="3.6068" y2="2.6162" width="0" layer="51"/>
<wire x1="3.6068" y1="2.6162" x2="4.5974" y2="2.6162" width="0" layer="51"/>
<wire x1="4.5974" y1="2.6162" x2="4.5974" y2="2.8956" width="0" layer="51"/>
<wire x1="4.5974" y1="2.8956" x2="3.6068" y2="2.8956" width="0" layer="51"/>
<wire x1="-3.6068" y1="2.3368" x2="-2.3368" y2="3.6068" width="0" layer="51"/>
<wire x1="-3.6068" y1="-3.6068" x2="3.6068" y2="-3.6068" width="0" layer="51"/>
<wire x1="3.6068" y1="-3.6068" x2="3.6068" y2="3.6068" width="0" layer="51"/>
<wire x1="3.6068" y1="3.6068" x2="-3.6068" y2="3.6068" width="0" layer="51"/>
<wire x1="-3.6068" y1="3.6068" x2="-3.6068" y2="-3.6068" width="0" layer="51"/>
<text x="-1.905" y="1.27" size="0.8128" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-2.1844" y="-3.175" size="0.8128" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="MK20DX256VLH7">
<pin name="D0/RX1/TOUCH" x="-27.94" y="50.8" length="middle"/>
<pin name="D1/TX1/TOUCH" x="-27.94" y="48.26" length="middle"/>
<pin name="D2" x="-27.94" y="45.72" length="middle"/>
<pin name="D3/CAN-TX/PWM" x="-27.94" y="43.18" length="middle"/>
<pin name="D4/CAN-RX/PWM" x="-27.94" y="40.64" length="middle"/>
<pin name="D5/PWM" x="-27.94" y="38.1" length="middle"/>
<pin name="D6/PWM" x="-27.94" y="35.56" length="middle"/>
<pin name="D7/RX3" x="-27.94" y="33.02" length="middle"/>
<pin name="D8/TX3" x="-27.94" y="30.48" length="middle"/>
<pin name="D9/RX2/PWM" x="-27.94" y="27.94" length="middle"/>
<pin name="D10/TX2/PWM" x="-27.94" y="25.4" length="middle"/>
<pin name="D11/MOSI" x="-27.94" y="22.86" length="middle"/>
<pin name="D12/MISO" x="-27.94" y="20.32" length="middle"/>
<pin name="D13/SCK/LED" x="-27.94" y="17.78" length="middle"/>
<pin name="D14/A0" x="-27.94" y="15.24" length="middle"/>
<pin name="D15/A1/TOUCH" x="-27.94" y="12.7" length="middle"/>
<pin name="D16/A2/TOUCH" x="-27.94" y="10.16" length="middle"/>
<pin name="D17/A3/TOUCH" x="-27.94" y="7.62" length="middle"/>
<pin name="D18/A4/SDA0/TOUCH" x="-27.94" y="5.08" length="middle"/>
<pin name="D19/A5/SCL0/TOUCH" x="-27.94" y="2.54" length="middle"/>
<pin name="D20/A6/PWM" x="-27.94" y="0" length="middle"/>
<pin name="D21/A7/PWM" x="-27.94" y="-2.54" length="middle"/>
<pin name="D22/A8/PWM/TOUCH" x="-27.94" y="-5.08" length="middle"/>
<pin name="D23/A9/PWM/TOUCH" x="-27.94" y="-7.62" length="middle"/>
<pin name="D24" x="-27.94" y="-10.16" length="middle"/>
<pin name="D25/PWM/TOUCH" x="-27.94" y="-12.7" length="middle"/>
<pin name="D26/A15" x="-27.94" y="-15.24" length="middle"/>
<pin name="D27/A16" x="-27.94" y="-17.78" length="middle"/>
<pin name="D28/A17" x="-27.94" y="-20.32" length="middle"/>
<pin name="D29/A18/SCL1" x="-27.94" y="-22.86" length="middle"/>
<pin name="D30/A19/SDA1" x="-27.94" y="-25.4" length="middle"/>
<pin name="D31/A20" x="-27.94" y="-27.94" length="middle"/>
<pin name="USB-M" x="30.48" y="-48.26" length="middle" rot="R180"/>
<pin name="USB-P" x="30.48" y="-45.72" length="middle" rot="R180"/>
<pin name="VREF-L" x="30.48" y="15.24" length="middle" rot="R180"/>
<pin name="VREF-H" x="30.48" y="35.56" length="middle" rot="R180"/>
<pin name="VSSA" x="30.48" y="12.7" length="middle" rot="R180"/>
<pin name="VCCA" x="30.48" y="38.1" length="middle" rot="R180"/>
<pin name="VSS" x="30.48" y="5.08" length="middle" rot="R180"/>
<pin name="VCC" x="30.48" y="48.26" length="middle" rot="R180"/>
<pin name="VOUT3V3" x="30.48" y="50.8" length="middle" rot="R180"/>
<pin name="VREGIN" x="30.48" y="53.34" length="middle" rot="R180"/>
<pin name="A13/ADC0_DM3" x="-27.94" y="-43.18" length="middle"/>
<pin name="A12/ADC0_DP3" x="-27.94" y="-40.64" length="middle"/>
<pin name="A11/ADC0_DP0" x="-27.94" y="-38.1" length="middle"/>
<pin name="A10/ADC0_DM0" x="-27.94" y="-35.56" length="middle"/>
<pin name="D33/PWM/TOUCH" x="-27.94" y="-33.02" length="middle"/>
<pin name="D32/PWM/TOUCH" x="-27.94" y="-30.48" length="middle"/>
<pin name="VREF_OUT" x="30.48" y="25.4" length="middle" rot="R180"/>
<pin name="A14/DAC" x="-27.94" y="-45.72" length="middle"/>
<pin name="OSC2" x="30.48" y="-40.64" length="middle" rot="R180"/>
<pin name="OSC1" x="30.48" y="-30.48" length="middle" rot="R180"/>
<pin name="PTA3" x="30.48" y="-25.4" length="middle" rot="R180"/>
<pin name="PTA2" x="30.48" y="-22.86" length="middle" rot="R180"/>
<pin name="PTA1" x="30.48" y="-20.32" length="middle" rot="R180"/>
<pin name="PTA0" x="30.48" y="-17.78" length="middle" rot="R180"/>
<pin name="RESET" x="30.48" y="-15.24" length="middle" rot="R180"/>
<pin name="EXTAL32" x="30.48" y="-10.16" length="middle" rot="R180"/>
<pin name="XTAL32" x="30.48" y="-5.08" length="middle" rot="R180"/>
<pin name="VBAT" x="30.48" y="0" length="middle" rot="R180"/>
<wire x1="-22.86" y1="55.88" x2="25.4" y2="55.88" width="0.254" layer="94"/>
<wire x1="25.4" y1="55.88" x2="25.4" y2="-50.8" width="0.254" layer="94"/>
<wire x1="25.4" y1="-50.8" x2="-22.86" y2="-50.8" width="0.254" layer="94"/>
<wire x1="-22.86" y1="-50.8" x2="-22.86" y2="55.88" width="0.254" layer="94"/>
<text x="-3.556" y="56.642" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-53.34" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="MINI54TAN">
<wire x1="-12.7" y1="17.78" x2="12.7" y2="17.78" width="0.254" layer="94"/>
<wire x1="12.7" y1="17.78" x2="12.7" y2="-17.78" width="0.254" layer="94"/>
<wire x1="12.7" y1="-17.78" x2="-12.7" y2="-17.78" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-17.78" x2="-12.7" y2="17.78" width="0.254" layer="94"/>
<pin name="VDD" x="-17.78" y="15.24" length="middle"/>
<pin name="P5.2" x="-17.78" y="7.62" length="middle"/>
<pin name="P3.2" x="-17.78" y="0" length="middle"/>
<pin name="P1.4" x="-17.78" y="-12.7" length="middle"/>
<pin name="P2.5" x="-17.78" y="-10.16" length="middle"/>
<pin name="VSS" x="-17.78" y="-7.62" length="middle"/>
<pin name="P3.5" x="17.78" y="-12.7" length="middle" rot="R180"/>
<pin name="P3.4" x="17.78" y="-10.16" length="middle" rot="R180"/>
<pin name="P0.0" x="17.78" y="15.24" length="middle" rot="R180"/>
<pin name="P0.6" x="17.78" y="12.7" length="middle" rot="R180"/>
<pin name="P0.5" x="17.78" y="10.16" length="middle" rot="R180"/>
<pin name="P0.7" x="17.78" y="7.62" length="middle" rot="R180"/>
<pin name="P0.1" x="17.78" y="5.08" length="middle" rot="R180"/>
<text x="-12.7" y="17.78" size="1.778" layer="95">&gt;NAME</text>
<text x="-12.7" y="-20.32" size="1.778" layer="96">&gt;VALUE</text>
<pin name="AVDD" x="-17.78" y="12.7" length="middle"/>
<pin name="AVSS" x="-17.78" y="-5.08" length="middle"/>
<pin name="LDOCAP" x="17.78" y="-2.54" length="middle" rot="R180"/>
<pin name="RESET" x="-17.78" y="5.08" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MK20DX256VLH7">
<description>This is a footprint for the MK20dx256VHL7, the chip at the heart of the Teensy 3.1. Notable upgrades over the Teensy 3.0 include more Flash Memory, RAM, a DAC output, additional ADC pins, etc.&lt;p&gt;Remember, if you want to use USB, VOut3v3 has to be attached to the 3.3V bus.</description>
<gates>
<gate name="G$1" symbol="MK20DX256VLH7" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QFP50P1200X1200X160-64N">
<connects>
<connect gate="G$1" pin="A10/ADC0_DM0" pad="10"/>
<connect gate="G$1" pin="A11/ADC0_DP0" pad="9"/>
<connect gate="G$1" pin="A12/ADC0_DP3" pad="11"/>
<connect gate="G$1" pin="A13/ADC0_DM3" pad="12"/>
<connect gate="G$1" pin="A14/DAC" pad="18"/>
<connect gate="G$1" pin="D0/RX1/TOUCH" pad="39"/>
<connect gate="G$1" pin="D1/TX1/TOUCH" pad="40"/>
<connect gate="G$1" pin="D10/TX2/PWM" pad="49"/>
<connect gate="G$1" pin="D11/MOSI" pad="51"/>
<connect gate="G$1" pin="D12/MISO" pad="52"/>
<connect gate="G$1" pin="D13/SCK/LED" pad="50"/>
<connect gate="G$1" pin="D14/A0" pad="58"/>
<connect gate="G$1" pin="D15/A1/TOUCH" pad="43"/>
<connect gate="G$1" pin="D16/A2/TOUCH" pad="35"/>
<connect gate="G$1" pin="D17/A3/TOUCH" pad="36"/>
<connect gate="G$1" pin="D18/A4/SDA0/TOUCH" pad="38"/>
<connect gate="G$1" pin="D19/A5/SCL0/TOUCH" pad="37"/>
<connect gate="G$1" pin="D2" pad="57"/>
<connect gate="G$1" pin="D20/A6/PWM" pad="62"/>
<connect gate="G$1" pin="D21/A7/PWM" pad="63"/>
<connect gate="G$1" pin="D22/A8/PWM/TOUCH" pad="44"/>
<connect gate="G$1" pin="D23/A9/PWM/TOUCH" pad="45"/>
<connect gate="G$1" pin="D24" pad="27"/>
<connect gate="G$1" pin="D25/PWM/TOUCH" pad="42"/>
<connect gate="G$1" pin="D26/A15" pad="2"/>
<connect gate="G$1" pin="D27/A16" pad="54"/>
<connect gate="G$1" pin="D28/A17" pad="53"/>
<connect gate="G$1" pin="D29/A18/SCL1" pad="55"/>
<connect gate="G$1" pin="D3/CAN-TX/PWM" pad="28"/>
<connect gate="G$1" pin="D30/A19/SDA1" pad="56"/>
<connect gate="G$1" pin="D31/A20" pad="1"/>
<connect gate="G$1" pin="D32/PWM/TOUCH" pad="41"/>
<connect gate="G$1" pin="D33/PWM/TOUCH" pad="26"/>
<connect gate="G$1" pin="D4/CAN-RX/PWM" pad="29"/>
<connect gate="G$1" pin="D5/PWM" pad="64"/>
<connect gate="G$1" pin="D6/PWM" pad="61"/>
<connect gate="G$1" pin="D7/RX3" pad="59"/>
<connect gate="G$1" pin="D8/TX3" pad="60"/>
<connect gate="G$1" pin="D9/RX2/PWM" pad="46"/>
<connect gate="G$1" pin="EXTAL32" pad="20"/>
<connect gate="G$1" pin="OSC1" pad="32"/>
<connect gate="G$1" pin="OSC2" pad="33"/>
<connect gate="G$1" pin="PTA0" pad="22"/>
<connect gate="G$1" pin="PTA1" pad="23"/>
<connect gate="G$1" pin="PTA2" pad="24"/>
<connect gate="G$1" pin="PTA3" pad="25"/>
<connect gate="G$1" pin="RESET" pad="34"/>
<connect gate="G$1" pin="USB-M" pad="6"/>
<connect gate="G$1" pin="USB-P" pad="5"/>
<connect gate="G$1" pin="VBAT" pad="21"/>
<connect gate="G$1" pin="VCC" pad="3 30 48"/>
<connect gate="G$1" pin="VCCA" pad="13"/>
<connect gate="G$1" pin="VOUT3V3" pad="7"/>
<connect gate="G$1" pin="VREF-H" pad="14"/>
<connect gate="G$1" pin="VREF-L" pad="15"/>
<connect gate="G$1" pin="VREF_OUT" pad="17"/>
<connect gate="G$1" pin="VREGIN" pad="8"/>
<connect gate="G$1" pin="VSS" pad="4 31 47"/>
<connect gate="G$1" pin="VSSA" pad="16"/>
<connect gate="G$1" pin="XTAL32" pad="19"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MINI54TAN">
<description>MINI54TAN Bootloader from PJRC.com, preprogrammed with Teensy 3.0 bootloader.

https://www.pjrc.com/store/ic_mini54_tqfp.html</description>
<gates>
<gate name="G$1" symbol="MINI54TAN" x="0" y="0"/>
</gates>
<devices>
<device name="DEFAULT" package="QFP50P900X900X160-48N">
<connects>
<connect gate="G$1" pin="AVDD" pad="43"/>
<connect gate="G$1" pin="AVSS" pad="5"/>
<connect gate="G$1" pin="LDOCAP" pad="18"/>
<connect gate="G$1" pin="P0.0" pad="38"/>
<connect gate="G$1" pin="P0.1" pad="37"/>
<connect gate="G$1" pin="P0.5" pad="34"/>
<connect gate="G$1" pin="P0.6" pad="33"/>
<connect gate="G$1" pin="P0.7" pad="32"/>
<connect gate="G$1" pin="P1.4" pad="47"/>
<connect gate="G$1" pin="P2.5" pad="25"/>
<connect gate="G$1" pin="P3.2" pad="8"/>
<connect gate="G$1" pin="P3.4" pad="9"/>
<connect gate="G$1" pin="P3.5" pad="10"/>
<connect gate="G$1" pin="P5.2" pad="20"/>
<connect gate="G$1" pin="RESET" pad="3"/>
<connect gate="G$1" pin="VDD" pad="42"/>
<connect gate="G$1" pin="VSS" pad="17"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Capacitors">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find resistors, capacitors, inductors, test points, jumper pads, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="EIA3216">
<wire x1="-1" y1="-1.2" x2="-2.5" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="-1.2" x2="-2.5" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="1.2" x2="-1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.2" x2="2.1" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.1" y1="-1.2" x2="2.5" y2="-0.8" width="0.2032" layer="21"/>
<wire x1="2.5" y1="-0.8" x2="2.5" y2="0.8" width="0.2032" layer="21"/>
<wire x1="2.5" y1="0.8" x2="2.1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="2.1" y1="1.2" x2="1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="0.381" y1="1.016" x2="0.381" y2="-1.016" width="0.127" layer="21"/>
<smd name="C" x="-1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<smd name="A" x="1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<text x="-2.54" y="1.381" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.408" y="1.332" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="EIA3528">
<wire x1="-0.9" y1="-1.6" x2="-2.6" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="-1.6" x2="-2.6" y2="1.55" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="1.55" x2="-0.9" y2="1.55" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.55" x2="2.2" y2="-1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="-1.55" x2="2.6" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="-1.2" x2="2.6" y2="1.25" width="0.2032" layer="21"/>
<wire x1="2.6" y1="1.25" x2="2.2" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="0.609" y1="1.311" x2="0.609" y2="-1.286" width="0.2032" layer="21" style="longdash"/>
<smd name="C" x="-1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<smd name="A" x="1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<text x="-2.27" y="-1.27" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="3.24" y="-1.37" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="CPOL-RADIAL-100UF-25V">
<wire x1="-0.635" y1="1.27" x2="-1.905" y2="1.27" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="3.25" width="0.2032" layer="21"/>
<pad name="2" x="-1.27" y="0" drill="0.7" diameter="1.651"/>
<pad name="1" x="1.27" y="0" drill="0.7" diameter="1.651" shape="square"/>
<text x="-1.905" y="-4.318" size="0.8128" layer="27">&gt;Value</text>
<text x="-0.762" y="1.651" size="0.4064" layer="25">&gt;Name</text>
</package>
<package name="CPOL-RADIAL-10UF-25V">
<wire x1="-0.762" y1="1.397" x2="-1.778" y2="1.397" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="2.5" width="0.2032" layer="21"/>
<pad name="1" x="1.27" y="0" drill="0.7" diameter="1.651" shape="square"/>
<pad name="2" x="-1.27" y="0" drill="0.7" diameter="1.651"/>
<text x="-0.889" y="1.524" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.905" y="-3.683" size="0.8128" layer="27">&gt;Value</text>
</package>
<package name="EIA7343">
<wire x1="-5" y1="2.5" x2="-2" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-5" y1="2.5" x2="-5" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="-5" y1="-2.5" x2="-2" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="2" y1="2.5" x2="4" y2="2.5" width="0.2032" layer="21"/>
<wire x1="4" y1="2.5" x2="5" y2="1.5" width="0.2032" layer="21"/>
<wire x1="5" y1="1.5" x2="5" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="5" y1="-1.5" x2="4" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="4" y1="-2.5" x2="2" y2="-2.5" width="0.2032" layer="21"/>
<smd name="C" x="-3.17" y="0" dx="2.55" dy="2.7" layer="1" rot="R180"/>
<smd name="A" x="3.17" y="0" dx="2.55" dy="2.7" layer="1" rot="R180"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="-1.27" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="PANASONIC_G">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package G&lt;/b&gt;</description>
<wire x1="-5.1" y1="5.1" x2="2.8" y2="5.1" width="0.1016" layer="51"/>
<wire x1="2.8" y1="5.1" x2="5.1" y2="2.8" width="0.1016" layer="51"/>
<wire x1="5.1" y1="2.8" x2="5.1" y2="-2.8" width="0.1016" layer="51"/>
<wire x1="5.1" y1="-2.8" x2="2.8" y2="-5.1" width="0.1016" layer="51"/>
<wire x1="2.8" y1="-5.1" x2="-5.1" y2="-5.1" width="0.1016" layer="51"/>
<wire x1="-5.1" y1="-5.1" x2="-5.1" y2="5.1" width="0.1016" layer="51"/>
<wire x1="-5.1" y1="1" x2="-5.1" y2="5.1" width="0.2032" layer="21"/>
<wire x1="-5.1" y1="5.1" x2="2.8" y2="5.1" width="0.2032" layer="21"/>
<wire x1="2.8" y1="5.1" x2="5.1" y2="2.8" width="0.2032" layer="21"/>
<wire x1="5.1" y1="2.8" x2="5.1" y2="1" width="0.2032" layer="21"/>
<wire x1="5.1" y1="-1" x2="5.1" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="5.1" y1="-2.8" x2="2.8" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="2.8" y1="-5.1" x2="-5.1" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="-5.1" y1="-5.1" x2="-5.1" y2="-1" width="0.2032" layer="21"/>
<wire x1="-4.85" y1="-1" x2="4.85" y2="-1" width="0.2032" layer="21" curve="156.699401" cap="flat"/>
<wire x1="-4.85" y1="1" x2="4.85" y2="1" width="0.2032" layer="21" curve="-156.699401" cap="flat"/>
<wire x1="-3.25" y1="3.7" x2="-3.25" y2="-3.65" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="4.95" width="0.1016" layer="51"/>
<smd name="-" x="-4.25" y="0" dx="3.9" dy="1.6" layer="1"/>
<smd name="+" x="4.25" y="0" dx="3.9" dy="1.6" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-5.85" y1="-0.45" x2="-4.9" y2="0.45" layer="51"/>
<rectangle x1="4.9" y1="-0.45" x2="5.85" y2="0.45" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-3.3" y="3.6"/>
<vertex x="-4.05" y="2.75"/>
<vertex x="-4.65" y="1.55"/>
<vertex x="-4.85" y="0.45"/>
<vertex x="-4.85" y="-0.45"/>
<vertex x="-4.65" y="-1.55"/>
<vertex x="-4.05" y="-2.75"/>
<vertex x="-3.3" y="-3.6"/>
<vertex x="-3.3" y="3.55"/>
</polygon>
</package>
<package name="PANASONIC_E">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package E&lt;/b&gt;</description>
<wire x1="-4.1" y1="4.1" x2="1.8" y2="4.1" width="0.1016" layer="51"/>
<wire x1="1.8" y1="4.1" x2="4.1" y2="1.8" width="0.1016" layer="51"/>
<wire x1="4.1" y1="1.8" x2="4.1" y2="-1.8" width="0.1016" layer="51"/>
<wire x1="4.1" y1="-1.8" x2="1.8" y2="-4.1" width="0.1016" layer="51"/>
<wire x1="1.8" y1="-4.1" x2="-4.1" y2="-4.1" width="0.1016" layer="51"/>
<wire x1="-4.1" y1="-4.1" x2="-4.1" y2="4.1" width="0.1016" layer="51"/>
<wire x1="-4.1" y1="0.9" x2="-4.1" y2="4.1" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="4.1" x2="1.8" y2="4.1" width="0.2032" layer="21"/>
<wire x1="1.8" y1="4.1" x2="4.1" y2="1.8" width="0.2032" layer="21"/>
<wire x1="4.1" y1="1.8" x2="4.1" y2="0.9" width="0.2032" layer="21"/>
<wire x1="4.1" y1="-0.9" x2="4.1" y2="-1.8" width="0.2032" layer="21"/>
<wire x1="4.1" y1="-1.8" x2="1.8" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="1.8" y1="-4.1" x2="-4.1" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="-4.1" x2="-4.1" y2="-0.9" width="0.2032" layer="21"/>
<wire x1="-2.2" y1="3.25" x2="-2.2" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="-3.85" y1="0.9" x2="3.85" y2="0.9" width="0.2032" layer="21" curve="-153.684915" cap="flat"/>
<wire x1="-3.85" y1="-0.9" x2="3.85" y2="-0.9" width="0.2032" layer="21" curve="153.684915" cap="flat"/>
<circle x="0" y="0" radius="3.95" width="0.1016" layer="51"/>
<smd name="-" x="-3" y="0" dx="3.8" dy="1.4" layer="1"/>
<smd name="+" x="3" y="0" dx="3.8" dy="1.4" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-4.5" y1="-0.35" x2="-3.8" y2="0.35" layer="51"/>
<rectangle x1="3.8" y1="-0.35" x2="4.5" y2="0.35" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-2.25" y="3.2"/>
<vertex x="-3" y="2.5"/>
<vertex x="-3.6" y="1.5"/>
<vertex x="-3.85" y="0.65"/>
<vertex x="-3.85" y="-0.65"/>
<vertex x="-3.55" y="-1.6"/>
<vertex x="-2.95" y="-2.55"/>
<vertex x="-2.25" y="-3.2"/>
<vertex x="-2.25" y="3.15"/>
</polygon>
</package>
<package name="PANASONIC_C">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package E&lt;/b&gt;</description>
<wire x1="-2.6" y1="2.45" x2="1.6" y2="2.45" width="0.2032" layer="21"/>
<wire x1="1.6" y1="2.45" x2="2.7" y2="1.35" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.75" x2="1.6" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="1.6" y1="-2.85" x2="-2.6" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="2.45" x2="1.6" y2="2.45" width="0.1016" layer="51"/>
<wire x1="1.6" y1="2.45" x2="2.7" y2="1.35" width="0.1016" layer="51"/>
<wire x1="2.7" y1="-1.75" x2="1.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="1.6" y1="-2.85" x2="-2.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="-2.6" y1="2.45" x2="-2.6" y2="0.35" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="-2.85" x2="-2.6" y2="-0.75" width="0.2032" layer="21"/>
<wire x1="2.7" y1="1.35" x2="2.7" y2="0.35" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.75" x2="2.7" y2="-0.7" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="2.45" x2="-2.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="2.7" y1="1.35" x2="2.7" y2="-1.75" width="0.1016" layer="51"/>
<wire x1="-2.4" y1="0.35" x2="2.45" y2="0.3" width="0.2032" layer="21" curve="-156.699401"/>
<wire x1="2.5" y1="-0.7" x2="-2.4" y2="-0.75" width="0.2032" layer="21" curve="-154.694887"/>
<circle x="0.05" y="-0.2" radius="2.5004" width="0.1016" layer="51"/>
<smd name="-" x="-1.8" y="-0.2" dx="2.2" dy="0.65" layer="1"/>
<smd name="+" x="1.9" y="-0.2" dx="2.2" dy="0.65" layer="1"/>
<text x="-2.6" y="2.7" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.6" y="-3.45" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="NIPPON_F80">
<wire x1="-3.3" y1="3.3" x2="1.7" y2="3.3" width="0.2032" layer="21"/>
<wire x1="1.7" y1="3.3" x2="3.3" y2="2" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-2" x2="1.7" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="1.7" y1="-3.3" x2="-3.3" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="3.3" x2="1.7" y2="3.3" width="0.1016" layer="51"/>
<wire x1="1.7" y1="3.3" x2="3.3" y2="2" width="0.1016" layer="51"/>
<wire x1="3.3" y1="-2" x2="1.7" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="1.7" y1="-3.3" x2="-3.3" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="-3.3" y1="3.3" x2="-3.3" y2="0.685" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="-3.3" x2="-3.3" y2="-0.685" width="0.2032" layer="21"/>
<wire x1="3.3" y1="2" x2="3.3" y2="0.685" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-2" x2="3.3" y2="-0.685" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="3.3" x2="-3.3" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="3.3" y1="2" x2="3.3" y2="-2" width="0.1016" layer="51"/>
<wire x1="-3.1" y1="0.685" x2="3.1" y2="0.685" width="0.2032" layer="21" curve="-156.500033"/>
<wire x1="3.1" y1="-0.685" x2="-3.1" y2="-0.685" width="0.2032" layer="21" curve="-154.748326"/>
<circle x="0" y="0" radius="3.15" width="0.1016" layer="51"/>
<smd name="-" x="-2.4" y="0" dx="2.95" dy="1" layer="1"/>
<smd name="+" x="2.4" y="0" dx="2.95" dy="1" layer="1"/>
<text x="-3.2" y="3.5" size="0.4064" layer="25">&gt;NAME</text>
<text x="-3.2" y="-3.85" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="PANASONIC_D">
<wire x1="-3.25" y1="3.25" x2="1.55" y2="3.25" width="0.1016" layer="51"/>
<wire x1="1.55" y1="3.25" x2="3.25" y2="1.55" width="0.1016" layer="51"/>
<wire x1="3.25" y1="1.55" x2="3.25" y2="-1.55" width="0.1016" layer="51"/>
<wire x1="3.25" y1="-1.55" x2="1.55" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="1.55" y1="-3.25" x2="-3.25" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="-3.25" y1="-3.25" x2="-3.25" y2="3.25" width="0.1016" layer="51"/>
<wire x1="-3.25" y1="0.95" x2="-3.25" y2="3.25" width="0.1016" layer="21"/>
<wire x1="-3.25" y1="3.25" x2="1.55" y2="3.25" width="0.1016" layer="21"/>
<wire x1="1.55" y1="3.25" x2="3.25" y2="1.55" width="0.1016" layer="21"/>
<wire x1="3.25" y1="1.55" x2="3.25" y2="0.95" width="0.1016" layer="21"/>
<wire x1="3.25" y1="-0.95" x2="3.25" y2="-1.55" width="0.1016" layer="21"/>
<wire x1="3.25" y1="-1.55" x2="1.55" y2="-3.25" width="0.1016" layer="21"/>
<wire x1="1.55" y1="-3.25" x2="-3.25" y2="-3.25" width="0.1016" layer="21"/>
<wire x1="-3.25" y1="-3.25" x2="-3.25" y2="-0.95" width="0.1016" layer="21"/>
<wire x1="2.95" y1="0.95" x2="-2.95" y2="0.95" width="0.1016" layer="21" curve="144.299363"/>
<wire x1="-2.95" y1="-0.95" x2="2.95" y2="-0.95" width="0.1016" layer="21" curve="144.299363"/>
<wire x1="-2.1" y1="2.25" x2="-2.1" y2="-2.2" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="3.1" width="0.1016" layer="51"/>
<smd name="+" x="2.4" y="0" dx="3" dy="1.4" layer="1"/>
<smd name="-" x="-2.4" y="0" dx="3" dy="1.4" layer="1"/>
<text x="-1.75" y="1" size="1.016" layer="25">&gt;NAME</text>
<text x="-1.75" y="-1.975" size="1.016" layer="27">&gt;VALUE</text>
<rectangle x1="-3.65" y1="-0.35" x2="-3.05" y2="0.35" layer="51"/>
<rectangle x1="3.05" y1="-0.35" x2="3.65" y2="0.35" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-2.15" y="2.15"/>
<vertex x="-2.6" y="1.6"/>
<vertex x="-2.9" y="0.9"/>
<vertex x="-3.05" y="0"/>
<vertex x="-2.9" y="-0.95"/>
<vertex x="-2.55" y="-1.65"/>
<vertex x="-2.15" y="-2.15"/>
<vertex x="-2.15" y="2.1"/>
</polygon>
</package>
<package name="CPOL-RADIAL-1000UF-63V">
<wire x1="-3.175" y1="1.905" x2="-4.445" y2="1.905" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="8.001" width="0.2032" layer="21"/>
<pad name="2" x="-3.81" y="0" drill="1.016" diameter="1.6764"/>
<pad name="1" x="3.81" y="0" drill="1.016" diameter="1.651" shape="square"/>
<text x="-2.54" y="8.89" size="0.8128" layer="27">&gt;Value</text>
<text x="-2.54" y="10.16" size="0.8128" layer="25">&gt;Name</text>
</package>
<package name="CPOL-RADIAL-1000UF-25V">
<wire x1="-1.905" y1="1.27" x2="-3.175" y2="1.27" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="5.461" width="0.2032" layer="21"/>
<pad name="-" x="-2.54" y="0" drill="0.9" diameter="1.9304"/>
<pad name="+" x="2.54" y="0" drill="0.9" diameter="1.9304" shape="square"/>
<text x="-1.905" y="-4.318" size="0.8128" layer="27">&gt;Value</text>
<text x="-0.762" y="2.921" size="0.4064" layer="25">&gt;Name</text>
</package>
<package name="VISHAY_C">
<wire x1="0" y1="1.27" x2="0" y2="1.905" width="0.254" layer="21"/>
<wire x1="-2.0574" y1="4.2926" x2="-2.0574" y2="-4.2926" width="0.127" layer="21"/>
<wire x1="-2.0574" y1="-4.2926" x2="2.0574" y2="-4.2926" width="0.127" layer="21"/>
<wire x1="2.0574" y1="-4.2926" x2="2.0574" y2="4.2926" width="0.127" layer="21"/>
<wire x1="2.0574" y1="4.2926" x2="-2.0574" y2="4.2926" width="0.127" layer="21"/>
<smd name="+" x="0" y="3.048" dx="3.556" dy="1.778" layer="1"/>
<smd name="-" x="0" y="-3.048" dx="3.556" dy="1.778" layer="1"/>
<text x="-1.905" y="4.445" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.905" y="-5.08" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="PANASONIC_H13">
<wire x1="-6.75" y1="6.75" x2="4" y2="6.75" width="0.1016" layer="51"/>
<wire x1="4" y1="6.75" x2="6.75" y2="4" width="0.1016" layer="51"/>
<wire x1="6.75" y1="4" x2="6.75" y2="-4" width="0.1016" layer="51"/>
<wire x1="6.75" y1="-4" x2="4" y2="-6.75" width="0.1016" layer="51"/>
<wire x1="4" y1="-6.75" x2="-6.75" y2="-6.75" width="0.1016" layer="51"/>
<wire x1="-6.75" y1="-6.75" x2="-6.75" y2="6.75" width="0.1016" layer="51"/>
<wire x1="-6.75" y1="1" x2="-6.75" y2="6.75" width="0.2032" layer="21"/>
<wire x1="-6.75" y1="6.75" x2="4" y2="6.75" width="0.2032" layer="21"/>
<wire x1="4" y1="6.75" x2="6.75" y2="4" width="0.2032" layer="21"/>
<wire x1="6.75" y1="4" x2="6.75" y2="1" width="0.2032" layer="21"/>
<wire x1="6.75" y1="-1" x2="6.75" y2="-4" width="0.2032" layer="21"/>
<wire x1="6.75" y1="-4" x2="4" y2="-6.75" width="0.2032" layer="21"/>
<wire x1="4" y1="-6.75" x2="-6.75" y2="-6.75" width="0.2032" layer="21"/>
<wire x1="-6.75" y1="-6.75" x2="-6.75" y2="-1" width="0.2032" layer="21"/>
<wire x1="-6.55" y1="-1.2" x2="6.45" y2="-1.2" width="0.2032" layer="21" curve="156.692742" cap="flat"/>
<wire x1="-6.55" y1="1.2" x2="6.55" y2="1.2" width="0.2032" layer="21" curve="-156.697982" cap="flat"/>
<wire x1="-5" y1="4.25" x2="-4.95" y2="-4.35" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="6.6" width="0.1016" layer="51"/>
<smd name="-" x="-4.7" y="0" dx="5" dy="1.6" layer="1"/>
<smd name="+" x="4.7" y="0" dx="5" dy="1.6" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-7.55" y1="-0.45" x2="-6.6" y2="0.45" layer="51"/>
<rectangle x1="6.6" y1="-0.45" x2="7.55" y2="0.45" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-5" y="4.2"/>
<vertex x="-5.75" y="3.15"/>
<vertex x="-6.25" y="2.05"/>
<vertex x="-6.55" y="0.45"/>
<vertex x="-6.55" y="-0.45"/>
<vertex x="-6.35" y="-1.65"/>
<vertex x="-5.75" y="-3.25"/>
<vertex x="-5" y="-4.2"/>
</polygon>
</package>
<package name="EIA6032">
<wire x1="3.2" y1="-1.6" x2="3.2" y2="1.6" width="0.127" layer="21"/>
<wire x1="-2.8" y1="-1.6" x2="3.2" y2="-1.6" width="0.127" layer="21"/>
<wire x1="3.2" y1="1.6" x2="-2.8" y2="1.6" width="0.127" layer="21"/>
<wire x1="-2.8" y1="1.6" x2="-3.4" y2="1" width="0.127" layer="21"/>
<wire x1="-3.4" y1="1" x2="-3.4" y2="-1" width="0.127" layer="21"/>
<wire x1="-2.8" y1="-1.6" x2="-3.4" y2="-1" width="0.127" layer="21"/>
<smd name="P$1" x="-2.3" y="0" dx="1.5" dy="2.4" layer="1"/>
<smd name="P$2" x="2.3" y="0" dx="1.5" dy="2.4" layer="1"/>
</package>
<package name="EN_J2">
<description>Type J2 package for SMD supercap PRT-10317 (p# EEC-EN0F204J2)</description>
<wire x1="-2.5" y1="-3.5" x2="2.5" y2="-3.5" width="0.127" layer="51"/>
<wire x1="-2.1" y1="3.5" x2="2.1" y2="3.5" width="0.127" layer="51"/>
<wire x1="-2.1" y1="3.5" x2="-2.5" y2="3.1" width="0.127" layer="51"/>
<wire x1="-2.5" y1="3.1" x2="-2.5" y2="2.3" width="0.127" layer="51"/>
<wire x1="2.1" y1="3.5" x2="2.5" y2="3.1" width="0.127" layer="51"/>
<wire x1="2.5" y1="3.1" x2="2.5" y2="2.3" width="0.127" layer="51"/>
<wire x1="-2.5" y1="-3.5" x2="-2.5" y2="-2.3" width="0.127" layer="51"/>
<wire x1="2.5" y1="-3.5" x2="2.5" y2="-2.3" width="0.127" layer="51"/>
<wire x1="-2.5908" y1="-2.413" x2="-2.5654" y2="2.4384" width="0.127" layer="21" curve="-91.212564"/>
<wire x1="2.5908" y1="-2.413" x2="2.5654" y2="2.4384" width="0.127" layer="21" curve="86.79344"/>
<wire x1="1.7272" y1="-1.27" x2="1.7272" y2="-2.0828" width="0.127" layer="21"/>
<wire x1="1.3462" y1="-1.6764" x2="2.159" y2="-1.6764" width="0.127" layer="21"/>
<circle x="0" y="0" radius="3.4" width="0.127" layer="51"/>
<smd name="-" x="0" y="2.8" dx="5" dy="2.4" layer="1"/>
<smd name="+" x="0" y="-3.2" dx="5" dy="1.6" layer="1"/>
<text x="-2.28" y="0.66" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.31" y="-1.21" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="EIA3528-KIT">
<description>&lt;h3&gt;EIA3528-KIT&lt;/h3&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has longer pads to make hand soldering easier.&lt;br&gt;</description>
<wire x1="-0.9" y1="-1.6" x2="-3.1" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="-1.6" x2="-3.1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="1.55" x2="-0.9" y2="1.55" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.55" x2="2.7" y2="-1.55" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.55" x2="3.1" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="3.1" y1="-1.2" x2="3.1" y2="1.25" width="0.2032" layer="21"/>
<wire x1="3.1" y1="1.25" x2="2.7" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.7" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="0.609" y1="1.311" x2="0.609" y2="-1.286" width="0.4" layer="21" style="longdash"/>
<smd name="C" x="-1.9" y="0" dx="1.7" dy="2.5" layer="1"/>
<smd name="A" x="1.9" y="0" dx="1.7" dy="2.5" layer="1"/>
<text x="-2.27" y="-1.27" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="3.24" y="-1.37" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="EIA3216-KIT">
<description>&lt;h3&gt;EIA3216-KIT&lt;/h3&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has longer pads to make hand soldering easier.&lt;br&gt;</description>
<wire x1="-1" y1="-1.2" x2="-3" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="-1.2" x2="-3" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="1.2" x2="-1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.2" x2="2.6" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="-1.2" x2="3" y2="-0.8" width="0.2032" layer="21"/>
<wire x1="3" y1="-0.8" x2="3" y2="0.8" width="0.2032" layer="21"/>
<wire x1="3" y1="0.8" x2="2.6" y2="1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="1.2" x2="1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="0.381" y1="1.016" x2="0.381" y2="-1.016" width="0.127" layer="21"/>
<smd name="C" x="-1.65" y="0" dx="1.9" dy="1.6" layer="1"/>
<smd name="A" x="1.65" y="0" dx="1.9" dy="1.6" layer="1"/>
<text x="-2.54" y="1.381" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.408" y="1.332" size="0.4064" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="CAP_POL">
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-1.016" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-1" x2="2.4892" y2="-1.8542" width="0.254" layer="94" curve="-37.878202" cap="flat"/>
<wire x1="-2.4669" y1="-1.8504" x2="0" y2="-1.0161" width="0.254" layer="94" curve="-37.376341" cap="flat"/>
<text x="1.016" y="0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.016" y="-4.191" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.253" y1="0.668" x2="-1.364" y2="0.795" layer="94"/>
<rectangle x1="-1.872" y1="0.287" x2="-1.745" y2="1.176" layer="94"/>
<pin name="+" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="-" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CAP_POL" prefix="C" uservalue="yes">
<description>&lt;b&gt;Capacitor Polarized&lt;/b&gt;
These are standard SMD and PTH capacitors. Normally 10uF, 47uF, and 100uF in electrolytic and tantalum varieties. Always verify the external diameter of the through hole cap, it varies with capacity, voltage, and manufacturer. The EIA devices should be standard.</description>
<gates>
<gate name="G$1" symbol="CAP_POL" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="EIA3216">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3528" package="EIA3528">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH1" package="CPOL-RADIAL-100UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH2" package="CPOL-RADIAL-10UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="7343" package="EIA7343">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CAP-08702"/>
</technology>
</technologies>
</device>
<device name="G" package="PANASONIC_G">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="E" package="PANASONIC_E">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="C" package="PANASONIC_C">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="F80" package="NIPPON_F80">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="D" package="PANASONIC_D">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH3" package="CPOL-RADIAL-1000UF-63V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH4" package="CPOL-RADIAL-1000UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="VISHAY_C">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="H13" package="PANASONIC_H13">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="6032" package="EIA6032">
<connects>
<connect gate="G$1" pin="+" pad="P$1"/>
<connect gate="G$1" pin="-" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="EN_J2" package="EN_J2">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3528-KIT" package="EIA3528-KIT">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206-KIT" package="EIA3216-KIT">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-DiscreteSemi">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find discrete semiconductors- transistors, diodes, TRIACs, optoisolators, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="SMA-DIODE">
<description>&lt;B&gt;Diode&lt;/B&gt;&lt;p&gt;
Basic SMA packaged diode. Good for reverse polarization protection. Common part #: MBRA140</description>
<wire x1="-2.3" y1="1" x2="-2.3" y2="1.45" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="1.45" x2="2.3" y2="1.45" width="0.2032" layer="21"/>
<wire x1="2.3" y1="1.45" x2="2.3" y2="1" width="0.2032" layer="21"/>
<wire x1="2.3" y1="-1" x2="2.3" y2="-1.45" width="0.2032" layer="21"/>
<wire x1="2.3" y1="-1.45" x2="-2.3" y2="-1.45" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-1.45" x2="-2.3" y2="-1" width="0.2032" layer="21"/>
<wire x1="1" y1="1" x2="1" y2="-1" width="0.2032" layer="21"/>
<smd name="A" x="-2.15" y="0" dx="1.27" dy="1.47" layer="1" rot="R180"/>
<smd name="C" x="2.15" y="0" dx="1.27" dy="1.47" layer="1"/>
<text x="-2.286" y="1.651" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.254" y="1.651" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="DIODE-1N4001">
<wire x1="3.175" y1="1.27" x2="1.905" y2="1.27" width="0.254" layer="21"/>
<wire x1="1.905" y1="1.27" x2="-3.175" y2="1.27" width="0.254" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-3.175" y2="0" width="0.254" layer="21"/>
<wire x1="-3.175" y1="0" x2="-3.175" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.254" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="3.175" y2="-1.27" width="0.254" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="3.175" y2="0" width="0.254" layer="21"/>
<wire x1="3.175" y1="0" x2="3.175" y2="1.27" width="0.254" layer="21"/>
<wire x1="1.905" y1="1.27" x2="1.905" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-3.175" y1="0" x2="-3.81" y2="0" width="0.254" layer="21"/>
<wire x1="3.175" y1="0" x2="3.81" y2="0" width="0.254" layer="21"/>
<pad name="A" x="-5.08" y="0" drill="1" diameter="1.9812"/>
<pad name="C" x="5.08" y="0" drill="1" diameter="1.9812"/>
<text x="-2.921" y="1.651" size="0.6096" layer="25">&gt;Name</text>
<text x="-2.921" y="-0.508" size="1.016" layer="21" ratio="12">&gt;Value</text>
</package>
<package name="SOD-323">
<wire x1="-0.9" y1="0.65" x2="-0.5" y2="0.65" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="0.65" x2="0.9" y2="0.65" width="0.2032" layer="21"/>
<wire x1="-0.9" y1="-0.65" x2="-0.5" y2="-0.65" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="-0.65" x2="0.9" y2="-0.65" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="0.65" x2="-0.5" y2="-0.65" width="0.2032" layer="21"/>
<smd name="C" x="-1.15" y="0" dx="0.63" dy="0.83" layer="1"/>
<smd name="A" x="1.15" y="0" dx="0.63" dy="0.83" layer="1"/>
<text x="-0.889" y="1.016" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="SOT23-3">
<wire x1="1.4224" y1="0.6604" x2="1.4224" y2="-0.6604" width="0.1524" layer="51"/>
<wire x1="1.4224" y1="-0.6604" x2="-1.4224" y2="-0.6604" width="0.1524" layer="51"/>
<wire x1="-1.4224" y1="-0.6604" x2="-1.4224" y2="0.6604" width="0.1524" layer="51"/>
<wire x1="-1.4224" y1="0.6604" x2="1.4224" y2="0.6604" width="0.1524" layer="51"/>
<wire x1="-0.8" y1="0.7" x2="-1.4" y2="0.7" width="0.2032" layer="21"/>
<wire x1="-1.4" y1="0.7" x2="-1.4" y2="-0.1" width="0.2032" layer="21"/>
<wire x1="0.8" y1="0.7" x2="1.4" y2="0.7" width="0.2032" layer="21"/>
<wire x1="1.4" y1="0.7" x2="1.4" y2="-0.1" width="0.2032" layer="21"/>
<smd name="1" x="-0.95" y="-1" dx="0.8" dy="0.9" layer="1"/>
<smd name="2" x="0.95" y="-1" dx="0.8" dy="0.9" layer="1"/>
<smd name="3" x="0" y="1.1" dx="0.8" dy="0.9" layer="1"/>
<text x="-0.8255" y="1.778" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-0.1905" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="DIODE-1N4148">
<wire x1="-2.54" y1="0.762" x2="2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0.762" x2="2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-0.762" x2="-2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="1.905" y1="0.635" x2="1.905" y2="-0.635" width="0.2032" layer="21"/>
<pad name="A" x="-3.81" y="0" drill="0.9" diameter="1.8796"/>
<pad name="C" x="3.81" y="0" drill="0.9" diameter="1.8796"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-2.032" y="-0.508" size="0.8128" layer="21">&gt;Value</text>
</package>
<package name="SMB-DIODE">
<description>&lt;b&gt;Diode&lt;/b&gt;&lt;p&gt;
Basic small signal diode good up to 200mA. SMB footprint. Common part #: BAS16</description>
<wire x1="-3.973" y1="1.983" x2="3.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="-1.983" x2="-3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-3.973" y1="-1.983" x2="-3.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="1.983" x2="3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-2.2606" y1="1.905" x2="2.2606" y2="1.905" width="0.1016" layer="21"/>
<wire x1="-2.2606" y1="-1.905" x2="2.2606" y2="-1.905" width="0.1016" layer="21"/>
<wire x1="-2.261" y1="-1.905" x2="-2.261" y2="1.905" width="0.1016" layer="51"/>
<wire x1="2.261" y1="-1.905" x2="2.261" y2="1.905" width="0.1016" layer="51"/>
<wire x1="0.643" y1="1" x2="-0.73" y2="0" width="0.2032" layer="21"/>
<wire x1="-0.73" y1="0" x2="0.643" y2="-1" width="0.2032" layer="21"/>
<wire x1="0.643" y1="-1" x2="0.643" y2="1" width="0.2032" layer="21"/>
<wire x1="-0.73" y1="1" x2="-0.73" y2="-1" width="0.2032" layer="21"/>
<smd name="C" x="-2.2" y="0" dx="2.4" dy="2.4" layer="1"/>
<smd name="A" x="2.2" y="0" dx="2.4" dy="2.4" layer="1"/>
<text x="-2.159" y="2.159" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.429" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-2.794" y1="-1.0922" x2="-2.2606" y2="1.0922" layer="51"/>
<rectangle x1="2.2606" y1="-1.0922" x2="2.794" y2="1.0922" layer="51"/>
</package>
<package name="DIODE-HV">
<wire x1="-3.973" y1="1.983" x2="3.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="-1.983" x2="-3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-3.973" y1="-1.983" x2="-3.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="1.983" x2="3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-2.2606" y1="1.905" x2="2.2606" y2="1.905" width="0.1016" layer="21"/>
<wire x1="-2.2606" y1="-1.905" x2="2.2606" y2="-1.905" width="0.1016" layer="21"/>
<wire x1="-2.261" y1="-1.905" x2="-2.261" y2="1.905" width="0.1016" layer="51"/>
<wire x1="2.261" y1="-1.905" x2="2.261" y2="1.905" width="0.1016" layer="51"/>
<wire x1="0.643" y1="1" x2="-0.73" y2="0" width="0.2032" layer="21"/>
<wire x1="-0.73" y1="0" x2="0.643" y2="-1" width="0.2032" layer="21"/>
<wire x1="0.643" y1="-1" x2="0.643" y2="1" width="0.2032" layer="21"/>
<wire x1="-0.73" y1="1" x2="-0.73" y2="-1" width="0.2032" layer="21"/>
<smd name="C" x="-2.454" y="0" dx="2.2" dy="2.4" layer="1"/>
<smd name="A" x="2.454" y="0" dx="2.2" dy="2.4" layer="1"/>
<text x="-2.159" y="2.159" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.429" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-2.794" y1="-1.0922" x2="-2.2606" y2="1.0922" layer="51"/>
<rectangle x1="2.2606" y1="-1.0922" x2="2.794" y2="1.0922" layer="51"/>
</package>
<package name="SMA-DIODE_ALT">
<wire x1="-2.3" y1="1.3" x2="-2.3" y2="1.45" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="1.45" x2="2.3" y2="1.45" width="0.2032" layer="21"/>
<wire x1="2.3" y1="1.45" x2="2.3" y2="1.3" width="0.2032" layer="21"/>
<wire x1="2.3" y1="-1.3" x2="2.3" y2="-1.45" width="0.2032" layer="21"/>
<wire x1="2.3" y1="-1.45" x2="-2.3" y2="-1.45" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-1.45" x2="-2.3" y2="-1.3" width="0.2032" layer="21"/>
<wire x1="0.6" y1="1" x2="0.6" y2="-1" width="0.2032" layer="21"/>
<smd name="A" x="-2" y="0" dx="2" dy="2" layer="1" rot="R180"/>
<smd name="C" x="2" y="0" dx="2" dy="2" layer="1"/>
<text x="-2.286" y="1.651" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.254" y="1.651" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="SMA-DIODE-KIT">
<wire x1="-2.3" y1="1" x2="-2.3" y2="1.45" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="1.45" x2="2.3" y2="1.45" width="0.2032" layer="21"/>
<wire x1="2.3" y1="1.45" x2="2.3" y2="1" width="0.2032" layer="21"/>
<wire x1="2.3" y1="-1" x2="2.3" y2="-1.45" width="0.2032" layer="21"/>
<wire x1="2.3" y1="-1.45" x2="-2.3" y2="-1.45" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-1.45" x2="-2.3" y2="-1" width="0.2032" layer="21"/>
<wire x1="1" y1="1" x2="1" y2="-1" width="0.2032" layer="21"/>
<smd name="A" x="-2.4" y="0" dx="1.77" dy="1.47" layer="1" rot="R180"/>
<smd name="C" x="2.4" y="0" dx="1.77" dy="1.47" layer="1"/>
<text x="-2.286" y="1.651" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.254" y="1.651" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="SOD523">
<wire x1="-0.59" y1="0.4" x2="0.59" y2="0.4" width="0.1016" layer="21"/>
<wire x1="0.59" y1="0.4" x2="0.59" y2="-0.4" width="0.1016" layer="51"/>
<wire x1="0.59" y1="-0.4" x2="-0.59" y2="-0.4" width="0.1016" layer="21"/>
<wire x1="-0.59" y1="-0.4" x2="-0.59" y2="0.4" width="0.1016" layer="51"/>
<rectangle x1="-0.75" y1="-0.17" x2="-0.54" y2="0.17" layer="51"/>
<rectangle x1="0.54" y1="-0.17" x2="0.75" y2="0.17" layer="51"/>
<rectangle x1="-0.59" y1="-0.4" x2="-0.3" y2="0.4" layer="51"/>
<smd name="A" x="0.7" y="0" dx="0.7" dy="0.5" layer="1"/>
<smd name="C" x="-0.6" y="0" dx="0.7" dy="0.5" layer="1"/>
<text x="-0.7366" y="0.5588" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.6858" y="-0.9906" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-0.1397" y1="-0.3937" x2="-0.0127" y2="0.381" layer="21"/>
</package>
<package name="SMC">
<description>&lt;b&gt;SMC Sized Diode&lt;/b&gt;</description>
<wire x1="-3.5" y1="3" x2="3.5" y2="3" width="0.2032" layer="21"/>
<wire x1="-3.5" y1="-3" x2="3.5" y2="-3" width="0.2032" layer="21"/>
<wire x1="-3.5" y1="-3" x2="-3.5" y2="3" width="0.127" layer="51"/>
<wire x1="3.5" y1="-3" x2="3.5" y2="3" width="0.127" layer="51"/>
<wire x1="0.543" y1="1" x2="-0.83" y2="0" width="0.2032" layer="21"/>
<wire x1="-0.83" y1="0" x2="0.543" y2="-1" width="0.2032" layer="21"/>
<wire x1="0.543" y1="-1" x2="0.543" y2="1" width="0.2032" layer="21"/>
<smd name="C" x="-3.302" y="0" dx="1.778" dy="3.175" layer="1"/>
<smd name="A" x="3.302" y="0" dx="1.778" dy="3.175" layer="1"/>
<text x="-0.635" y="1.905" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.635" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-4" y1="-1.5" x2="-3.5" y2="1.5" layer="51"/>
<rectangle x1="3.5" y1="-1.5" x2="4" y2="1.5" layer="51"/>
<rectangle x1="-1.7" y1="-3" x2="-1.3" y2="3" layer="21"/>
<wire x1="-3.5" y1="3" x2="-3.5" y2="2" width="0.2032" layer="21"/>
<wire x1="-3.5" y1="-3" x2="-3.5" y2="-2" width="0.2032" layer="21"/>
<wire x1="3.5" y1="3" x2="3.5" y2="2" width="0.2032" layer="21"/>
<wire x1="3.5" y1="-3" x2="3.5" y2="-2" width="0.2032" layer="21"/>
</package>
<package name="DIODE-1N4148-KIT">
<wire x1="-2.54" y1="0.762" x2="2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0.762" x2="2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-0.762" x2="-2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="1.905" y1="0.635" x2="1.905" y2="-0.635" width="0.2032" layer="21"/>
<pad name="A" x="-3.81" y="0" drill="0.9" diameter="1.8796" stop="no"/>
<pad name="C" x="3.81" y="0" drill="0.9" diameter="1.8796" stop="no"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-2.032" y="-0.508" size="0.8128" layer="21">&gt;Value</text>
<circle x="-3.81" y="0" radius="0.4572" width="0" layer="29"/>
<circle x="-3.81" y="0" radius="0.9398" width="0" layer="30"/>
<circle x="-3.81" y="0" radius="0.4572" width="0" layer="29"/>
<circle x="3.81" y="0" radius="0.4572" width="0" layer="29"/>
<circle x="3.81" y="0" radius="0.9398" width="0" layer="30"/>
</package>
<package name="DIODE-1N4001-KIT">
<wire x1="3.175" y1="1.27" x2="1.905" y2="1.27" width="0.254" layer="21"/>
<wire x1="1.905" y1="1.27" x2="-3.175" y2="1.27" width="0.254" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-3.175" y2="0" width="0.254" layer="21"/>
<wire x1="-3.175" y1="0" x2="-3.175" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.254" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="3.175" y2="-1.27" width="0.254" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="3.175" y2="0" width="0.254" layer="21"/>
<wire x1="3.175" y1="0" x2="3.175" y2="1.27" width="0.254" layer="21"/>
<wire x1="1.905" y1="1.27" x2="1.905" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-3.175" y1="0" x2="-3.81" y2="0" width="0.254" layer="21"/>
<wire x1="3.175" y1="0" x2="3.81" y2="0" width="0.254" layer="21"/>
<pad name="A" x="-5.08" y="0" drill="1.016" diameter="1.8796" stop="no"/>
<pad name="C" x="5.08" y="0" drill="1.016" diameter="1.8796" stop="no"/>
<text x="-2.921" y="1.651" size="0.6096" layer="25">&gt;Name</text>
<text x="-2.921" y="-0.508" size="1.016" layer="21" ratio="12">&gt;Value</text>
<circle x="-5.08" y="0" radius="0.508" width="0" layer="29"/>
<circle x="5.08" y="0" radius="0.508" width="0" layer="29"/>
<circle x="-5.08" y="0" radius="0.9906" width="0" layer="30"/>
<circle x="5.08" y="0" radius="0.9906" width="0" layer="30"/>
</package>
<package name="SOD-123">
<description>100V/150mA 1N4148 - Super Cheap</description>
<wire x1="-1.3" y1="0.775" x2="-0.5" y2="0.775" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="0.775" x2="1.3" y2="0.775" width="0.2032" layer="21"/>
<wire x1="-1.3" y1="-0.775" x2="-0.5" y2="-0.775" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="-0.775" x2="1.3" y2="-0.775" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="0.775" x2="-0.5" y2="-0.775" width="0.2032" layer="21"/>
<smd name="C" x="-1.575" y="0" dx="0.9" dy="0.95" layer="1"/>
<smd name="A" x="1.575" y="0" dx="0.9" dy="0.95" layer="1"/>
<text x="-0.889" y="1.016" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
<wire x1="-1.35" y1="0.775" x2="1.35" y2="0.775" width="0.127" layer="51"/>
<wire x1="1.35" y1="0.775" x2="1.35" y2="-0.775" width="0.127" layer="51"/>
<wire x1="1.35" y1="-0.775" x2="-1.35" y2="-0.775" width="0.127" layer="51"/>
<wire x1="-1.35" y1="-0.775" x2="-1.35" y2="0.775" width="0.127" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="DIODE">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<text x="2.54" y="0.4826" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.3114" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="point" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="point" direction="pas" rot="R180"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.1524" layer="94"/>
<wire x1="2.54" y1="0" x2="1.27" y2="0" width="0.1524" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="DIODE" prefix="D" uservalue="yes">
<description>&lt;b&gt;Diode&lt;/b&gt;
These are standard reverse protection diodes and small signal diodes. SMA package can handle up to about 1A. SOD-323 can handle about 200mA. What the SOD-323 package when ordering, there are some mfgs out there that are 5-pin packages.</description>
<gates>
<gate name="G$1" symbol="DIODE" x="0" y="0"/>
</gates>
<devices>
<device name="SMA" package="SMA-DIODE">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH" package="DIODE-1N4001">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="BAS16" package="SOD-323">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="DIO-09646" constant="no"/>
<attribute name="VALUE" value="250mA/100V" constant="no"/>
</technology>
</technologies>
</device>
<device name="SOT23" package="SOT23-3">
<connects>
<connect gate="G$1" pin="A" pad="1"/>
<connect gate="G$1" pin="C" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1N4148" package="DIODE-1N4148">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMB" package="SMB-DIODE">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="DIO-09646" constant="no"/>
</technology>
</technologies>
</device>
<device name="HV" package="DIODE-HV">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMA-ALT" package="SMA-DIODE_ALT">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMA-KIT" package="SMA-DIODE-KIT">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SOD523" package="SOD523">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="ES3J" package="SMC">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="DIO-12441" constant="no"/>
<attribute name="VALUE" value="3A/600V" constant="no"/>
</technology>
</technologies>
</device>
<device name="KIT" package="DIODE-1N4148-KIT">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="KIT2" package="DIODE-1N4001-KIT">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SOD123" package="SOD-123">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Connectors">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find connectors and sockets- basically anything that can be plugged into or onto.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="1X06">
<wire x1="11.43" y1="0.635" x2="12.065" y2="1.27" width="0.2032" layer="21"/>
<wire x1="12.065" y1="1.27" x2="13.335" y2="1.27" width="0.2032" layer="21"/>
<wire x1="13.335" y1="1.27" x2="13.97" y2="0.635" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-0.635" x2="13.335" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="13.335" y1="-1.27" x2="12.065" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="12.065" y1="-1.27" x2="11.43" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="6.985" y1="1.27" x2="8.255" y2="1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="1.27" x2="8.89" y2="0.635" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-0.635" x2="8.255" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.89" y1="0.635" x2="9.525" y2="1.27" width="0.2032" layer="21"/>
<wire x1="9.525" y1="1.27" x2="10.795" y2="1.27" width="0.2032" layer="21"/>
<wire x1="10.795" y1="1.27" x2="11.43" y2="0.635" width="0.2032" layer="21"/>
<wire x1="11.43" y1="-0.635" x2="10.795" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="10.795" y1="-1.27" x2="9.525" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="9.525" y1="-1.27" x2="8.89" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.635" x2="4.445" y2="1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.715" y2="1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="5.715" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="4.445" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="6.985" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="-1.27" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="13.97" y1="0.635" x2="13.97" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="4" x="7.62" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="5" x="10.16" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="6" x="12.7" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="12.446" y1="-0.254" x2="12.954" y2="0.254" layer="51"/>
<rectangle x1="9.906" y1="-0.254" x2="10.414" y2="0.254" layer="51"/>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="MOLEX-1X6">
<wire x1="-1.27" y1="3.048" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="13.97" y1="3.048" x2="13.97" y2="-2.54" width="0.127" layer="21"/>
<wire x1="13.97" y1="3.048" x2="-1.27" y2="3.048" width="0.127" layer="21"/>
<wire x1="13.97" y1="-2.54" x2="12.7" y2="-2.54" width="0.127" layer="21"/>
<wire x1="12.7" y1="-2.54" x2="0" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.27" width="0.127" layer="21"/>
<wire x1="0" y1="-1.27" x2="12.7" y2="-1.27" width="0.127" layer="21"/>
<wire x1="12.7" y1="-1.27" x2="12.7" y2="-2.54" width="0.127" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" shape="square"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796"/>
<pad name="4" x="7.62" y="0" drill="1.016" diameter="1.8796"/>
<pad name="5" x="10.16" y="0" drill="1.016" diameter="1.8796"/>
<pad name="6" x="12.7" y="0" drill="1.016" diameter="1.8796"/>
</package>
<package name="MOLEX-1X6-RA">
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="3.175" width="0.127" layer="21"/>
<wire x1="13.97" y1="0.635" x2="13.97" y2="3.175" width="0.127" layer="21"/>
<wire x1="13.97" y1="0.635" x2="-1.27" y2="0.635" width="0.127" layer="21"/>
<wire x1="13.97" y1="3.175" x2="12.7" y2="3.175" width="0.127" layer="21"/>
<wire x1="12.7" y1="3.175" x2="0" y2="3.175" width="0.127" layer="21"/>
<wire x1="0" y1="3.175" x2="-1.27" y2="3.175" width="0.127" layer="21"/>
<wire x1="0" y1="3.175" x2="0" y2="7.62" width="0.127" layer="21"/>
<wire x1="0" y1="7.62" x2="12.7" y2="7.62" width="0.127" layer="21"/>
<wire x1="12.7" y1="7.62" x2="12.7" y2="3.175" width="0.127" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" shape="square"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796"/>
<pad name="4" x="7.62" y="0" drill="1.016" diameter="1.8796"/>
<pad name="5" x="10.16" y="0" drill="1.016" diameter="1.8796"/>
<pad name="6" x="12.7" y="0" drill="1.016" diameter="1.8796"/>
<text x="-0.889" y="-2.794" size="1.27" layer="25">&gt;NAME</text>
<text x="8.001" y="-2.794" size="1.27" layer="25">&gt;VALUE</text>
</package>
<package name="1X06-SMD">
<wire x1="7.62" y1="1.25" x2="-7.62" y2="1.25" width="0.127" layer="51"/>
<wire x1="-7.62" y1="1.25" x2="-7.62" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-7.62" y1="-1.25" x2="-6.35" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-6.35" y1="-1.25" x2="-3.81" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-3.81" y1="-1.25" x2="-1.27" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-1.27" y1="-1.25" x2="1.27" y2="-1.25" width="0.127" layer="51"/>
<wire x1="1.27" y1="-1.25" x2="3.81" y2="-1.25" width="0.127" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="6.35" y2="-1.25" width="0.127" layer="51"/>
<wire x1="6.35" y1="-1.25" x2="7.62" y2="-1.25" width="0.127" layer="51"/>
<wire x1="7.62" y1="-1.25" x2="7.62" y2="1.25" width="0.127" layer="51"/>
<wire x1="6.35" y1="-1.25" x2="6.35" y2="-7.25" width="0.127" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="3.81" y2="-7.25" width="0.127" layer="51"/>
<wire x1="1.27" y1="-1.25" x2="1.27" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-1.27" y1="-1.25" x2="-1.27" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-3.81" y1="-1.25" x2="-3.81" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-6.35" y1="-1.25" x2="-6.35" y2="-7.25" width="0.127" layer="51"/>
<smd name="4" x="1.27" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="5" x="3.81" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="6" x="6.35" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="3" x="-1.27" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="2" x="-3.81" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="1" x="-6.35" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<hole x="-5.08" y="0" drill="1.4"/>
<hole x="5.08" y="0" drill="1.4"/>
</package>
<package name="1X06_LOCK">
<description>This footprint was designed to help hold the alignment of a through-hole component (i.e.  6-pin header) while soldering it into place.  
You may notice that each hole has been shifted either up or down by 0.005 of an inch from it's more standard position (which is a perfectly straight line).  
This slight alteration caused the pins (the squares in the middle) to touch the edges of the holes.  Because they are alternating, it causes a "brace" 
to hold the component in place.  0.005 has proven to be the perfect amount of "off-center" position when using our standard breakaway headers.
Although looks a little odd when you look at the bare footprint, once you have a header in there, the alteration is very hard to notice.  Also,
if you push a header all the way into place, it is covered up entirely on the bottom side.  This idea of altering the position of holes to aid alignment 
will be further integrated into the Sparkfun Library for other footprints.  It can help hold any component with 3 or more connection pins.</description>
<wire x1="-1.27" y1="0.508" x2="-0.635" y2="1.143" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.143" x2="0.635" y2="1.143" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.143" x2="1.27" y2="0.508" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.508" x2="1.905" y2="1.143" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.143" x2="3.175" y2="1.143" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.143" x2="3.81" y2="0.508" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.508" x2="4.445" y2="1.143" width="0.2032" layer="21"/>
<wire x1="4.445" y1="1.143" x2="5.715" y2="1.143" width="0.2032" layer="21"/>
<wire x1="5.715" y1="1.143" x2="6.35" y2="0.508" width="0.2032" layer="21"/>
<wire x1="6.35" y1="0.508" x2="6.985" y2="1.143" width="0.2032" layer="21"/>
<wire x1="6.985" y1="1.143" x2="8.255" y2="1.143" width="0.2032" layer="21"/>
<wire x1="8.255" y1="1.143" x2="8.89" y2="0.508" width="0.2032" layer="21"/>
<wire x1="8.89" y1="0.508" x2="9.525" y2="1.143" width="0.2032" layer="21"/>
<wire x1="9.525" y1="1.143" x2="10.795" y2="1.143" width="0.2032" layer="21"/>
<wire x1="10.795" y1="1.143" x2="11.43" y2="0.508" width="0.2032" layer="21"/>
<wire x1="11.43" y1="0.508" x2="12.065" y2="1.143" width="0.2032" layer="21"/>
<wire x1="12.065" y1="1.143" x2="13.335" y2="1.143" width="0.2032" layer="21"/>
<wire x1="13.335" y1="1.143" x2="13.97" y2="0.508" width="0.2032" layer="21"/>
<wire x1="13.97" y1="0.508" x2="13.97" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-0.762" x2="13.335" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="13.335" y1="-1.397" x2="12.065" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="12.065" y1="-1.397" x2="11.43" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="11.43" y1="-0.762" x2="10.795" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="10.795" y1="-1.397" x2="9.525" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="9.525" y1="-1.397" x2="8.89" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-0.762" x2="8.255" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="8.255" y1="-1.397" x2="6.985" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="6.985" y1="-1.397" x2="6.35" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.762" x2="5.715" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="5.715" y1="-1.397" x2="4.445" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="4.445" y1="-1.397" x2="3.81" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.762" x2="3.175" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.397" x2="1.905" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.397" x2="1.27" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.762" x2="0.635" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.397" x2="-0.635" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="-1.397" x2="-1.27" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.762" x2="-1.27" y2="0.508" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.508" x2="1.27" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.508" x2="3.81" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="6.35" y1="0.508" x2="6.35" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="8.89" y1="0.508" x2="8.89" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="11.43" y1="0.508" x2="11.43" y2="-0.762" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796"/>
<pad name="2" x="2.54" y="-0.254" drill="1.016" diameter="1.8796"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796"/>
<pad name="4" x="7.62" y="-0.254" drill="1.016" diameter="1.8796"/>
<pad name="5" x="10.16" y="0" drill="1.016" diameter="1.8796"/>
<pad name="6" x="12.7" y="-0.254" drill="1.016" diameter="1.8796"/>
<text x="-1.27" y="1.778" size="1.27" layer="25" font="vector">&gt;NAME</text>
<text x="-1.27" y="-3.302" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.2921" y1="-0.4191" x2="0.2921" y2="0.1651" layer="51"/>
<rectangle x1="2.2479" y1="-0.4191" x2="2.8321" y2="0.1651" layer="51"/>
<rectangle x1="4.7879" y1="-0.4191" x2="5.3721" y2="0.1651" layer="51"/>
<rectangle x1="7.3279" y1="-0.4191" x2="7.9121" y2="0.1651" layer="51"/>
<rectangle x1="9.8679" y1="-0.4191" x2="10.4521" y2="0.1651" layer="51"/>
<rectangle x1="12.4079" y1="-0.4191" x2="12.9921" y2="0.1651" layer="51"/>
</package>
<package name="1X06_LOCK_LONGPADS">
<description>This footprint was designed to help hold the alignment of a through-hole component (i.e.  6-pin header) while soldering it into place.  
You may notice that each hole has been shifted either up or down by 0.005 of an inch from it's more standard position (which is a perfectly straight line).  
This slight alteration caused the pins (the squares in the middle) to touch the edges of the holes.  Because they are alternating, it causes a "brace" 
to hold the component in place.  0.005 has proven to be the perfect amount of "off-center" position when using our standard breakaway headers.
Although looks a little odd when you look at the bare footprint, once you have a header in there, the alteration is very hard to notice.  Also,
if you push a header all the way into place, it is covered up entirely on the bottom side.  This idea of altering the position of holes to aid alignment 
will be further integrated into the Sparkfun Library for other footprints.  It can help hold any component with 3 or more connection pins.</description>
<wire x1="1.524" y1="-0.127" x2="1.016" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="4.064" y1="-0.127" x2="3.556" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="6.604" y1="-0.127" x2="6.096" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="9.144" y1="-0.127" x2="8.636" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="11.684" y1="-0.127" x2="11.176" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.127" x2="-1.016" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.127" x2="-1.27" y2="0.8636" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.8636" x2="-0.9906" y2="1.143" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.127" x2="-1.27" y2="-1.1176" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-1.1176" x2="-0.9906" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-0.127" x2="13.716" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-0.127" x2="13.97" y2="-1.1176" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-1.1176" x2="13.6906" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-0.127" x2="13.97" y2="0.8636" width="0.2032" layer="21"/>
<wire x1="13.97" y1="0.8636" x2="13.6906" y2="1.143" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="2.54" y="-0.254" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="7.62" y="-0.254" drill="1.016" shape="long" rot="R90"/>
<pad name="5" x="10.16" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="6" x="12.7" y="-0.254" drill="1.016" shape="long" rot="R90"/>
<text x="-1.27" y="1.778" size="1.27" layer="25" font="vector">&gt;NAME</text>
<text x="-1.27" y="-3.302" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.2921" y1="-0.4191" x2="0.2921" y2="0.1651" layer="51"/>
<rectangle x1="2.2479" y1="-0.4191" x2="2.8321" y2="0.1651" layer="51"/>
<rectangle x1="4.7879" y1="-0.4191" x2="5.3721" y2="0.1651" layer="51"/>
<rectangle x1="7.3279" y1="-0.4191" x2="7.9121" y2="0.1651" layer="51" rot="R90"/>
<rectangle x1="9.8679" y1="-0.4191" x2="10.4521" y2="0.1651" layer="51"/>
<rectangle x1="12.4079" y1="-0.4191" x2="12.9921" y2="0.1651" layer="51"/>
</package>
<package name="MOLEX-1X6_LOCK">
<description>This footprint was designed to help hold the alignment of a through-hole component (i.e.  6-pin header) while soldering it into place.  
You may notice that each hole has been shifted either up or down by 0.005 of an inch from it's more standard position (which is a perfectly straight line).  
This slight alteration caused the pins (the squares in the middle) to touch the edges of the holes.  Because they are alternating, it causes a "brace" 
to hold the component in place.  0.005 has proven to be the perfect amount of "off-center" position when using our standard breakaway headers.
Although looks a little odd when you look at the bare footprint, once you have a header in there, the alteration is very hard to notice.  Also,
if you push a header all the way into place, it is covered up entirely on the bottom side.  This idea of altering the position of holes to aid alignment 
will be further integrated into the Sparkfun Library for other footprints.  It can help hold any component with 3 or more connection pins.</description>
<wire x1="-1.27" y1="3.048" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="13.97" y1="3.048" x2="13.97" y2="-2.54" width="0.127" layer="21"/>
<wire x1="13.97" y1="3.048" x2="-1.27" y2="3.048" width="0.127" layer="21"/>
<wire x1="13.97" y1="-2.54" x2="12.7" y2="-2.54" width="0.127" layer="21"/>
<wire x1="12.7" y1="-2.54" x2="0" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.27" width="0.127" layer="21"/>
<wire x1="0" y1="-1.27" x2="12.7" y2="-1.27" width="0.127" layer="21"/>
<wire x1="12.7" y1="-1.27" x2="12.7" y2="-2.54" width="0.127" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796"/>
<pad name="2" x="2.54" y="-0.254" drill="1.016" diameter="1.8796"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796"/>
<pad name="4" x="7.62" y="-0.254" drill="1.016" diameter="1.8796"/>
<pad name="5" x="10.16" y="0" drill="1.016" diameter="1.8796"/>
<pad name="6" x="12.7" y="-0.254" drill="1.016" diameter="1.8796"/>
<text x="-1.27" y="3.302" size="1.27" layer="25" font="vector">&gt;NAME</text>
<text x="-1.27" y="-4.064" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.2921" y1="-0.4191" x2="0.2921" y2="0.1651" layer="51"/>
<rectangle x1="2.2479" y1="-0.4191" x2="2.8321" y2="0.1651" layer="51"/>
<rectangle x1="4.7879" y1="-0.4191" x2="5.3721" y2="0.1651" layer="51"/>
<rectangle x1="7.3279" y1="-0.4191" x2="7.9121" y2="0.1651" layer="51"/>
<rectangle x1="9.8679" y1="-0.4191" x2="10.4521" y2="0.1651" layer="51"/>
<rectangle x1="12.4079" y1="-0.4191" x2="12.9921" y2="0.1651" layer="51"/>
</package>
<package name="MOLEX-1X6-RA_LOCK">
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="3.175" width="0.127" layer="21"/>
<wire x1="13.97" y1="0.635" x2="13.97" y2="3.175" width="0.127" layer="21"/>
<wire x1="13.97" y1="0.635" x2="-1.27" y2="0.635" width="0.127" layer="21"/>
<wire x1="13.97" y1="3.175" x2="12.7" y2="3.175" width="0.127" layer="21"/>
<wire x1="12.7" y1="3.175" x2="0" y2="3.175" width="0.127" layer="21"/>
<wire x1="0" y1="3.175" x2="-1.27" y2="3.175" width="0.127" layer="21"/>
<wire x1="0" y1="3.175" x2="0" y2="7.62" width="0.127" layer="21"/>
<wire x1="0" y1="7.62" x2="12.7" y2="7.62" width="0.127" layer="21"/>
<wire x1="12.7" y1="7.62" x2="12.7" y2="3.175" width="0.127" layer="21"/>
<pad name="1" x="0" y="0.127" drill="1.016" diameter="1.8796" shape="square"/>
<pad name="2" x="2.54" y="-0.127" drill="1.016" diameter="1.8796"/>
<pad name="3" x="5.08" y="0.127" drill="1.016" diameter="1.8796"/>
<pad name="4" x="7.62" y="-0.127" drill="1.016" diameter="1.8796"/>
<pad name="5" x="10.16" y="0.127" drill="1.016" diameter="1.8796"/>
<pad name="6" x="12.7" y="-0.127" drill="1.016" diameter="1.8796"/>
<text x="-0.889" y="-2.794" size="1.27" layer="25">&gt;NAME</text>
<text x="8.001" y="-2.794" size="1.27" layer="25">&gt;VALUE</text>
</package>
<package name="1X06-SIP_LOCK">
<description>This footprint was designed to help hold the alignment of a through-hole component (i.e.  6-pin header) while soldering it into place.  
You may notice that each hole has been shifted either up or down by 0.005 of an inch from it's more standard position (which is a perfectly straight line).  
This slight alteration caused the pins (the squares in the middle) to touch the edges of the holes.  Because they are alternating, it causes a "brace" 
to hold the component in place.  0.005 has proven to be the perfect amount of "off-center" position when using our standard breakaway headers.
Although looks a little odd when you look at the bare footprint, once you have a header in there, the alteration is very hard to notice.  Also,
if you push a header all the way into place, it is covered up entirely on the bottom side.  This idea of altering the position of holes to aid alignment 
will be further integrated into the Sparkfun Library for other footprints.  It can help hold any component with 3 or more connection pins.</description>
<wire x1="11.43" y1="0.635" x2="12.065" y2="1.27" width="0.2032" layer="21"/>
<wire x1="12.065" y1="1.27" x2="13.335" y2="1.27" width="0.2032" layer="21"/>
<wire x1="13.335" y1="1.27" x2="13.97" y2="0.635" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-0.635" x2="13.335" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="13.335" y1="-1.27" x2="12.065" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="12.065" y1="-1.27" x2="11.43" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="6.985" y1="1.27" x2="8.255" y2="1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="1.27" x2="8.89" y2="0.635" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-0.635" x2="8.255" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.89" y1="0.635" x2="9.525" y2="1.27" width="0.2032" layer="21"/>
<wire x1="9.525" y1="1.27" x2="10.795" y2="1.27" width="0.2032" layer="21"/>
<wire x1="10.795" y1="1.27" x2="11.43" y2="0.635" width="0.2032" layer="21"/>
<wire x1="11.43" y1="-0.635" x2="10.795" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="10.795" y1="-1.27" x2="9.525" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="9.525" y1="-1.27" x2="8.89" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.635" x2="4.445" y2="1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.715" y2="1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="5.715" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="4.445" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="6.985" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="-1.27" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="13.97" y1="0.635" x2="13.97" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796"/>
<pad name="2" x="2.54" y="-0.254" drill="1.016" diameter="1.8796"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796"/>
<pad name="4" x="7.62" y="-0.254" drill="1.016" diameter="1.8796"/>
<pad name="5" x="10.16" y="0" drill="1.016" diameter="1.8796"/>
<pad name="6" x="12.7" y="-0.254" drill="1.016" diameter="1.8796"/>
<text x="-1.27" y="1.524" size="1.27" layer="25" font="vector">&gt;NAME</text>
<text x="-1.27" y="-2.921" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.2921" y1="-0.4191" x2="0.2921" y2="0.1651" layer="51"/>
<rectangle x1="2.2479" y1="-0.4191" x2="2.8321" y2="0.1651" layer="51"/>
<rectangle x1="4.7879" y1="-0.4191" x2="5.3721" y2="0.1651" layer="51"/>
<rectangle x1="7.3279" y1="-0.4191" x2="7.9121" y2="0.1651" layer="51"/>
<rectangle x1="9.8679" y1="-0.4191" x2="10.4521" y2="0.1651" layer="51"/>
<rectangle x1="12.4079" y1="-0.4191" x2="12.9921" y2="0.1651" layer="51"/>
</package>
<package name="1X06_FEMALE_LOCK.010">
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="1.27" x2="13.97" y2="1.27" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-1.27" x2="-1.27" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="13.97" y1="1.27" x2="13.97" y2="-1.27" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0.254" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="-0.254" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0.254" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="4" x="7.62" y="-0.254" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="5" x="10.16" y="0.254" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="6" x="12.7" y="-0.254" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.3175" y1="-0.1905" x2="0.3175" y2="0.1905" layer="51"/>
<rectangle x1="2.2225" y1="-0.1905" x2="2.8575" y2="0.1905" layer="51"/>
<rectangle x1="4.7625" y1="-0.1905" x2="5.3975" y2="0.1905" layer="51"/>
<rectangle x1="7.3025" y1="-0.1905" x2="7.9375" y2="0.1905" layer="51"/>
<rectangle x1="9.8425" y1="-0.1905" x2="10.4775" y2="0.1905" layer="51"/>
<rectangle x1="12.3825" y1="-0.1905" x2="13.0175" y2="0.1905" layer="51"/>
</package>
<package name="1X06_LONGPADS">
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="13.97" y1="0.635" x2="13.97" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<pad name="4" x="7.62" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<pad name="5" x="10.16" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<pad name="6" x="12.7" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<text x="-1.3462" y="2.4638" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.81" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="12.446" y1="-0.254" x2="12.954" y2="0.254" layer="51"/>
<rectangle x1="9.906" y1="-0.254" x2="10.414" y2="0.254" layer="51"/>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="1X06-SMD_EDGE">
<wire x1="13.97" y1="-2.54" x2="-1.27" y2="-2.54" width="0.127" layer="51"/>
<wire x1="-1.27" y1="-2.54" x2="-1.27" y2="-11.176" width="0.127" layer="51"/>
<wire x1="-1.27" y1="-11.176" x2="13.97" y2="-11.176" width="0.127" layer="51"/>
<wire x1="13.97" y1="-11.176" x2="13.97" y2="-2.54" width="0.127" layer="51"/>
<smd name="4" x="7.62" y="-0.08" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="5" x="10.16" y="-0.08" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="6" x="12.7" y="-0.08" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="3" x="5.08" y="-0.08" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="2" x="2.54" y="-0.08" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="1" x="0" y="-0.08" dx="3" dy="1" layer="1" rot="R90"/>
<text x="0" y="-6.35" size="0.4064" layer="51">thru-hole vertical Female Header</text>
<text x="0" y="-7.62" size="0.4064" layer="51">used as an SMD part </text>
<text x="0" y="-8.89" size="0.4064" layer="51">(placed horizontally, at board's edge)</text>
<rectangle x1="-0.381" y1="-2.4892" x2="0.381" y2="0.2794" layer="51"/>
<rectangle x1="2.159" y1="-2.4892" x2="2.921" y2="0.2794" layer="51"/>
<rectangle x1="4.699" y1="-2.4892" x2="5.461" y2="0.2794" layer="51"/>
<rectangle x1="7.239" y1="-2.4892" x2="8.001" y2="0.2794" layer="51"/>
<rectangle x1="9.779" y1="-2.4892" x2="10.541" y2="0.2794" layer="51"/>
<rectangle x1="12.319" y1="-2.4892" x2="13.081" y2="0.2794" layer="51"/>
</package>
<package name="SCREWTERMINAL-3.5MM-6">
<wire x1="-2.3" y1="3.4" x2="19.76" y2="3.4" width="0.2032" layer="21"/>
<wire x1="19.76" y1="3.4" x2="19.76" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="19.76" y1="-2.8" x2="19.76" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="19.76" y1="-3.6" x2="-2.3" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-3.6" x2="-2.3" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-2.8" x2="-2.3" y2="3.4" width="0.2032" layer="21"/>
<wire x1="19.76" y1="-2.8" x2="-2.3" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-1.35" x2="-2.7" y2="-1.35" width="0.2032" layer="51"/>
<wire x1="-2.7" y1="-1.35" x2="-2.7" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="-2.7" y1="-2.35" x2="-2.3" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="19.76" y1="3.15" x2="20.16" y2="3.15" width="0.2032" layer="51"/>
<wire x1="20.16" y1="3.15" x2="20.16" y2="2.15" width="0.2032" layer="51"/>
<wire x1="20.16" y1="2.15" x2="19.76" y2="2.15" width="0.2032" layer="51"/>
<pad name="1" x="0" y="0" drill="1.2" diameter="2.032" shape="square"/>
<pad name="2" x="3.5" y="0" drill="1.2" diameter="2.032"/>
<pad name="3" x="7" y="0" drill="1.2" diameter="2.032"/>
<pad name="4" x="10.5" y="0" drill="1.2" diameter="2.032"/>
<pad name="5" x="14" y="0" drill="1.2" diameter="2.032"/>
<pad name="6" x="17.5" y="0" drill="1.2" diameter="2.032"/>
<text x="-1.27" y="2.54" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="1.27" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1X06-SMD-FEMALE">
<wire x1="-7.62" y1="4.05" x2="7.62" y2="4.05" width="0.2032" layer="51"/>
<wire x1="7.62" y1="4.05" x2="7.62" y2="-4.05" width="0.2032" layer="51"/>
<wire x1="7.62" y1="-4.05" x2="-7.62" y2="-4.05" width="0.2032" layer="51"/>
<wire x1="-7.62" y1="-4.05" x2="-7.62" y2="4.05" width="0.2032" layer="51"/>
<wire x1="-6.85" y1="-3" x2="-6.85" y2="-2" width="0.2032" layer="21"/>
<wire x1="-6.85" y1="-2" x2="-5.85" y2="-2" width="0.2032" layer="21"/>
<wire x1="-5.85" y1="-2" x2="-5.85" y2="-3" width="0.2032" layer="21"/>
<wire x1="-7.1" y1="4" x2="-7.6" y2="4" width="0.2032" layer="21"/>
<wire x1="-7.6" y1="4" x2="-7.6" y2="-4" width="0.2032" layer="21"/>
<wire x1="-7.6" y1="-4" x2="-7.1" y2="-4" width="0.2032" layer="21"/>
<wire x1="7.1" y1="4" x2="7.6" y2="4" width="0.2032" layer="21"/>
<wire x1="7.6" y1="4" x2="7.6" y2="-4" width="0.2032" layer="21"/>
<wire x1="7.6" y1="-4" x2="7.1" y2="-4" width="0.2032" layer="21"/>
<wire x1="-0.3" y1="4" x2="0.3" y2="4" width="0.2032" layer="21"/>
<wire x1="-2.8" y1="4" x2="-2.2" y2="4" width="0.2032" layer="21"/>
<wire x1="-5.4" y1="4" x2="-4.8" y2="4" width="0.2032" layer="21"/>
<wire x1="2.3" y1="4" x2="2.9" y2="4" width="0.2032" layer="21"/>
<wire x1="4.8" y1="4" x2="5.4" y2="4" width="0.2032" layer="21"/>
<wire x1="4.8" y1="-4" x2="5.4" y2="-4" width="0.2032" layer="21"/>
<wire x1="2.2" y1="-4" x2="2.8" y2="-4" width="0.2032" layer="21"/>
<wire x1="-0.3" y1="-4" x2="0.3" y2="-4" width="0.2032" layer="21"/>
<wire x1="-2.8" y1="-4" x2="-2.2" y2="-4" width="0.2032" layer="21"/>
<wire x1="-5.4" y1="-4" x2="-4.8" y2="-4" width="0.2032" layer="21"/>
<smd name="6" x="6.35" y="-4.62" dx="1.02" dy="2.16" layer="1"/>
<smd name="5" x="3.81" y="-4.62" dx="1.02" dy="2.16" layer="1"/>
<smd name="4" x="1.27" y="-4.62" dx="1.02" dy="2.16" layer="1"/>
<smd name="3" x="-1.27" y="-4.62" dx="1.02" dy="2.16" layer="1"/>
<smd name="2" x="-3.81" y="-4.62" dx="1.02" dy="2.16" layer="1"/>
<smd name="1" x="-6.35" y="-4.62" dx="1.02" dy="2.16" layer="1"/>
<smd name="A1" x="-6.35" y="4.62" dx="1.02" dy="2.16" layer="1"/>
<smd name="A2" x="-3.81" y="4.62" dx="1.02" dy="2.16" layer="1"/>
<smd name="A3" x="-1.27" y="4.62" dx="1.02" dy="2.16" layer="1"/>
<smd name="A4" x="1.27" y="4.62" dx="1.02" dy="2.16" layer="1"/>
<smd name="A5" x="3.81" y="4.62" dx="1.02" dy="2.16" layer="1"/>
<smd name="A6" x="6.35" y="4.62" dx="1.02" dy="2.16" layer="1"/>
</package>
<package name="1X06-SMD-FEMALE-V2">
<description>Package for 4UCONN part #19686 *UNPROVEN*</description>
<wire x1="-7.5" y1="0.45" x2="-7.5" y2="-8.05" width="0.127" layer="21"/>
<wire x1="7.5" y1="0.45" x2="-7.5" y2="0.45" width="0.127" layer="21"/>
<wire x1="7.5" y1="-8.05" x2="7.5" y2="0.45" width="0.127" layer="21"/>
<wire x1="-7.5" y1="-8.05" x2="7.5" y2="-8.05" width="0.127" layer="21"/>
<smd name="4" x="-1.27" y="3.425" dx="1.25" dy="3" layer="1" rot="R180"/>
<smd name="5" x="-3.81" y="3.425" dx="1.25" dy="3" layer="1" rot="R180"/>
<smd name="6" x="-6.35" y="3.425" dx="1.25" dy="3" layer="1" rot="R180"/>
<smd name="3" x="1.27" y="3.425" dx="1.25" dy="3" layer="1" rot="R180"/>
<smd name="2" x="3.81" y="3.425" dx="1.25" dy="3" layer="1" rot="R180"/>
<smd name="1" x="6.35" y="3.425" dx="1.25" dy="3" layer="1" rot="R180"/>
<text x="7.6" y="-8.3" size="1" layer="27" rot="R180">&gt;Value</text>
<text x="-7.4" y="-9.3" size="1" layer="25">&gt;Name</text>
</package>
<package name="1X06_HOLES_ONLY">
<circle x="0" y="0" radius="0.635" width="0.127" layer="51"/>
<circle x="2.54" y="0" radius="0.635" width="0.127" layer="51"/>
<circle x="5.08" y="0" radius="0.635" width="0.127" layer="51"/>
<circle x="7.62" y="0" radius="0.635" width="0.127" layer="51"/>
<circle x="10.16" y="0" radius="0.635" width="0.127" layer="51"/>
<circle x="12.7" y="0" radius="0.635" width="0.127" layer="51"/>
<pad name="1" x="0" y="0" drill="0.889" diameter="0.8128" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="0.889" diameter="0.8128" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="0.889" diameter="0.8128" rot="R90"/>
<pad name="4" x="7.62" y="0" drill="0.889" diameter="0.8128" rot="R90"/>
<pad name="5" x="10.16" y="0" drill="0.889" diameter="0.8128" rot="R90"/>
<pad name="6" x="12.7" y="0" drill="0.889" diameter="0.8128" rot="R90"/>
<hole x="0" y="0" drill="1.4732"/>
<hole x="2.54" y="0" drill="1.4732"/>
<hole x="5.08" y="0" drill="1.4732"/>
<hole x="7.62" y="0" drill="1.4732"/>
<hole x="10.16" y="0" drill="1.4732"/>
<hole x="12.7" y="0" drill="1.4732"/>
</package>
<package name="1X06_SMD_STRAIGHT">
<wire x1="1.37" y1="1.25" x2="-14.07" y2="1.25" width="0.127" layer="51"/>
<wire x1="-14.07" y1="1.25" x2="-14.07" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-14.07" y1="-1.25" x2="1.37" y2="-1.25" width="0.127" layer="51"/>
<wire x1="1.37" y1="-1.25" x2="1.37" y2="1.25" width="0.127" layer="51"/>
<wire x1="1.37" y1="1.25" x2="1.37" y2="-1.25" width="0.127" layer="21"/>
<wire x1="-14.07" y1="-1.25" x2="-14.07" y2="1.25" width="0.127" layer="21"/>
<wire x1="0.85" y1="1.25" x2="1.37" y2="1.25" width="0.127" layer="21"/>
<wire x1="-14.07" y1="1.25" x2="-10.883" y2="1.25" width="0.127" layer="21"/>
<wire x1="-13.55" y1="-1.25" x2="-14.07" y2="-1.25" width="0.127" layer="21"/>
<wire x1="1.37" y1="-1.25" x2="-1.817" y2="-1.25" width="0.127" layer="21"/>
<wire x1="-4.377" y1="1.25" x2="-0.703" y2="1.25" width="0.127" layer="21"/>
<wire x1="-9.457" y1="1.25" x2="-5.783" y2="1.25" width="0.127" layer="21"/>
<wire x1="-3.329" y1="-1.25" x2="-6.831" y2="-1.25" width="0.127" layer="21"/>
<wire x1="-8.409" y1="-1.25" x2="-11.911" y2="-1.25" width="0.127" layer="21"/>
<smd name="5" x="-10.16" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="3" x="-5.08" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="1" x="0" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="6" x="-12.7" y="-1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="4" x="-7.62" y="-1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="2" x="-2.54" y="-1.65" dx="2" dy="1" layer="1" rot="R90"/>
<text x="-13.97" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-13.97" y="-4.191" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="1X06_SMD_STRAIGHT_ALT">
<wire x1="1.37" y1="1.25" x2="-14.07" y2="1.25" width="0.127" layer="51"/>
<wire x1="-14.07" y1="1.25" x2="-14.07" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-14.07" y1="-1.25" x2="1.37" y2="-1.25" width="0.127" layer="51"/>
<wire x1="1.37" y1="-1.25" x2="1.37" y2="1.25" width="0.127" layer="51"/>
<wire x1="-14.07" y1="1.25" x2="-14.07" y2="-1.25" width="0.127" layer="21"/>
<wire x1="1.37" y1="-1.25" x2="1.37" y2="1.25" width="0.127" layer="21"/>
<wire x1="-13.55" y1="1.25" x2="-14.07" y2="1.25" width="0.127" layer="21"/>
<wire x1="1.37" y1="1.25" x2="-1.817" y2="1.25" width="0.127" layer="21"/>
<wire x1="0.85" y1="-1.25" x2="1.37" y2="-1.25" width="0.127" layer="21"/>
<wire x1="-14.07" y1="-1.25" x2="-10.883" y2="-1.25" width="0.127" layer="21"/>
<wire x1="-8.323" y1="1.25" x2="-11.997" y2="1.25" width="0.127" layer="21"/>
<wire x1="-3.243" y1="1.25" x2="-6.917" y2="1.25" width="0.127" layer="21"/>
<wire x1="-9.371" y1="-1.25" x2="-5.869" y2="-1.25" width="0.127" layer="21"/>
<wire x1="-4.291" y1="-1.25" x2="-0.789" y2="-1.25" width="0.127" layer="21"/>
<smd name="5" x="-10.16" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="3" x="-5.08" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="1" x="0" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="6" x="-12.7" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="4" x="-7.62" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="2" x="-2.54" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<text x="-13.97" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-13.97" y="-4.191" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="1X06_SMD_STRAIGHT_COMBO">
<wire x1="12.7" y1="1.27" x2="12.7" y2="-1.27" width="0.4064" layer="1"/>
<wire x1="10.16" y1="1.27" x2="10.16" y2="-1.27" width="0.4064" layer="1"/>
<wire x1="7.62" y1="1.27" x2="7.62" y2="-1.27" width="0.4064" layer="1"/>
<wire x1="5.08" y1="1.27" x2="5.08" y2="-1.27" width="0.4064" layer="1"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="-1.27" width="0.4064" layer="1"/>
<wire x1="0" y1="1.27" x2="0" y2="-1.27" width="0.4064" layer="1"/>
<wire x1="-1.37" y1="-1.25" x2="-1.37" y2="1.25" width="0.1778" layer="21"/>
<wire x1="14.07" y1="1.25" x2="14.07" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="-0.73" y1="-1.25" x2="-1.37" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="14.07" y1="-1.25" x2="13.4" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="13.4" y1="1.25" x2="14.07" y2="1.25" width="0.1778" layer="21"/>
<wire x1="-1.37" y1="1.25" x2="-0.73" y2="1.25" width="0.1778" layer="21"/>
<wire x1="10.949" y1="1.25" x2="11.911" y2="1.25" width="0.1778" layer="21"/>
<wire x1="10.949" y1="-1.29" x2="11.911" y2="-1.29" width="0.1778" layer="21"/>
<wire x1="8.409" y1="1.25" x2="9.371" y2="1.25" width="0.1778" layer="21"/>
<wire x1="8.409" y1="-1.29" x2="9.371" y2="-1.29" width="0.1778" layer="21"/>
<wire x1="5.869" y1="-1.29" x2="6.831" y2="-1.29" width="0.1778" layer="21"/>
<wire x1="5.869" y1="1.25" x2="6.831" y2="1.25" width="0.1778" layer="21"/>
<wire x1="3.329" y1="-1.29" x2="4.291" y2="-1.29" width="0.1778" layer="21"/>
<wire x1="3.329" y1="1.25" x2="4.291" y2="1.25" width="0.1778" layer="21"/>
<wire x1="0.789" y1="-1.29" x2="1.751" y2="-1.29" width="0.1778" layer="21"/>
<wire x1="0.789" y1="1.25" x2="1.751" y2="1.25" width="0.1778" layer="21"/>
<smd name="5" x="10.16" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="3" x="5.08" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="1" x="0" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="6" x="12.7" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="4" x="7.62" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="2" x="2.54" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="1-2" x="0" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="2-2" x="2.54" y="-1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="3-2" x="5.08" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="4-2" x="7.62" y="-1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="5-2" x="10.16" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="6-2" x="12.7" y="-1.65" dx="2" dy="1" layer="1" rot="R90"/>
<text x="0" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="0" y="-4.191" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="BTA">
<description>British Telecom connector, used for Vernier sensors (analog)</description>
<hole x="6.45" y="0" drill="3.2"/>
<hole x="-6.45" y="0" drill="3.2"/>
<pad name="1" x="4.75" y="9" drill="1.4" diameter="2.54" shape="square" rot="R90"/>
<pad name="2" x="3.25" y="6" drill="1.4" diameter="2.54"/>
<pad name="3" x="1.75" y="9" drill="1.4" diameter="2.54"/>
<pad name="5" x="-1.25" y="9" drill="1.4" diameter="2.54"/>
<pad name="4" x="0.25" y="6" drill="1.4" diameter="2.54"/>
<pad name="6" x="-2.75" y="6" drill="1.4" diameter="2.54"/>
<wire x1="-8" y1="-7.5" x2="-8" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="-7.95" y1="-3.8" x2="-7.95" y2="9.9" width="0.2032" layer="21"/>
<wire x1="-8" y1="-7.5" x2="7.9" y2="-7.5" width="0.2032" layer="21"/>
<wire x1="7.9" y1="-7.5" x2="7.9" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="7.95" y1="-3.8" x2="7.95" y2="9.9" width="0.2032" layer="21"/>
<wire x1="-7.95" y1="9.9" x2="7.95" y2="9.9" width="0.2032" layer="21"/>
<wire x1="-8.925" y1="-3.8" x2="-8.925" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="8.925" y1="-3.8" x2="8.925" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="-8.925" y1="-5.1" x2="-8" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="7.9" y1="-5.1" x2="8.925" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="-8.925" y1="-3.8" x2="-7.95" y2="-3.8" width="0.2032" layer="21"/>
<wire x1="-7.95" y1="-3.8" x2="7.95" y2="-3.8" width="0.2032" layer="21"/>
<wire x1="7.95" y1="-3.8" x2="8.925" y2="-3.8" width="0.2032" layer="21"/>
<text x="-2.92" y="-7.07" size="1.27" layer="25">&gt;NAME</text>
<wire x1="-8" y1="-5.1" x2="7.9" y2="-5.1" width="0.2032" layer="21"/>
</package>
<package name="BTD">
<description>British Telecom connector, used for Vernier sensors (digital)</description>
<hole x="6.45" y="0" drill="3.2"/>
<hole x="-6.45" y="0" drill="3.2"/>
<wire x1="-7.95" y1="-3.8" x2="-7.95" y2="9.9" width="0.2032" layer="21"/>
<wire x1="-7.95" y1="-7.5" x2="7.95" y2="-7.5" width="0.2032" layer="21"/>
<wire x1="7.95" y1="-3.8" x2="7.95" y2="9.9" width="0.2032" layer="21"/>
<wire x1="-7.95" y1="9.9" x2="7.95" y2="9.9" width="0.2032" layer="21"/>
<wire x1="-8.975" y1="-3.8" x2="-8.975" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="8.875" y1="-3.8" x2="8.875" y2="-5.1" width="0.2032" layer="21"/>
<pad name="2" x="-3.25" y="9" drill="1.4" diameter="2.54" rot="R180"/>
<pad name="1" x="-4.75" y="6" drill="1.4" diameter="2.54" shape="square" rot="R180"/>
<pad name="4" x="-0.25" y="9" drill="1.4" diameter="2.54" rot="R180"/>
<pad name="6" x="2.75" y="9" drill="1.4" diameter="2.54" rot="R180"/>
<pad name="3" x="-1.75" y="6" drill="1.4" diameter="2.54" rot="R180"/>
<pad name="5" x="1.25" y="6" drill="1.4" diameter="2.54" rot="R180"/>
<wire x1="-8.975" y1="-5.1" x2="-7.95" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="-7.95" y1="-5.1" x2="7.95" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="7.95" y1="-5.1" x2="8.875" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="-8.975" y1="-3.8" x2="-7.95" y2="-3.8" width="0.2032" layer="21"/>
<wire x1="-7.95" y1="-3.8" x2="7.95" y2="-3.8" width="0.2032" layer="21"/>
<wire x1="7.95" y1="-7.5" x2="7.95" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="-7.95" y1="-7.5" x2="-7.95" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="7.95" y1="-3.8" x2="8.875" y2="-3.8" width="0.2032" layer="21"/>
<text x="-3" y="-7" size="1.27" layer="25">&gt;Name</text>
</package>
<package name="1X06_SMD_MALE">
<text x="-1" y="3.321" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1" y="-4.591" size="1.27" layer="27">&gt;VALUE</text>
<wire x1="-1.27" y1="1.25" x2="-1.27" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-1.27" y1="-1.25" x2="13.97" y2="-1.25" width="0.127" layer="51"/>
<wire x1="13.97" y1="-1.25" x2="13.97" y2="1.25" width="0.127" layer="51"/>
<wire x1="13.97" y1="1.25" x2="-1.27" y2="1.25" width="0.127" layer="51"/>
<circle x="0" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="2.54" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="5.08" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="7.62" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="10.16" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="12.7" y="0" radius="0.64" width="0.127" layer="51"/>
<rectangle x1="-0.32" y1="0" x2="0.32" y2="2.75" layer="51"/>
<rectangle x1="4.76" y1="0" x2="5.4" y2="2.75" layer="51"/>
<rectangle x1="9.84" y1="0" x2="10.48" y2="2.75" layer="51"/>
<rectangle x1="2.22" y1="-2.75" x2="2.86" y2="0" layer="51" rot="R180"/>
<rectangle x1="7.3" y1="-2.75" x2="7.94" y2="0" layer="51" rot="R180"/>
<rectangle x1="12.38" y1="-2.75" x2="13.02" y2="0" layer="51" rot="R180"/>
<smd name="1" x="0" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="2" x="2.54" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="3" x="5.08" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="4" x="7.62" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="5" x="10.16" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="6" x="12.7" y="0" dx="1.02" dy="6" layer="1"/>
<wire x1="-1.27" y1="1.25" x2="-1.27" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="-1.27" y1="-1.25" x2="-0.635" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="-1.27" y1="1.25" x2="-0.635" y2="1.25" width="0.1778" layer="21"/>
<wire x1="0.762" y1="1.25" x2="1.778" y2="1.25" width="0.1778" layer="21"/>
<wire x1="3.302" y1="1.25" x2="4.318" y2="1.25" width="0.1778" layer="21"/>
<wire x1="5.842" y1="1.25" x2="6.858" y2="1.25" width="0.1778" layer="21"/>
<wire x1="8.382" y1="1.25" x2="9.398" y2="1.25" width="0.1778" layer="21"/>
<wire x1="10.922" y1="1.25" x2="11.938" y2="1.25" width="0.1778" layer="21"/>
<wire x1="1.778" y1="-1.25" x2="0.762" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="4.318" y1="-1.25" x2="3.302" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="6.858" y1="-1.25" x2="5.842" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="9.398" y1="-1.25" x2="8.382" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="11.938" y1="-1.25" x2="10.922" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="13.97" y1="-1.25" x2="13.97" y2="1.25" width="0.1778" layer="21"/>
<wire x1="13.97" y1="-1.25" x2="13.335" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="13.97" y1="1.25" x2="13.335" y2="1.25" width="0.1778" layer="21"/>
</package>
<package name="1X06-1MM">
<description>Works with part #579 (https://www.sparkfun.com/products/579). Commonly used on GPS modules EM408, EM406 and GP-635T. Also compatible with cable 9123 (https://www.sparkfun.com/products/9123) and cable 574 (https://www.sparkfun.com/products/574).</description>
<circle x="-3.6" y="1.2" radius="0.1047" width="0.4064" layer="51"/>
<wire x1="-2.54" y1="-1.651" x2="2.54" y2="-1.651" width="0.254" layer="21"/>
<wire x1="-4.318" y1="0.508" x2="-4.318" y2="1.905" width="0.254" layer="21"/>
<wire x1="3.302" y1="1.905" x2="4.318" y2="1.905" width="0.254" layer="21"/>
<wire x1="4.318" y1="1.905" x2="4.318" y2="0.508" width="0.254" layer="21"/>
<wire x1="-4.318" y1="1.905" x2="-3.302" y2="1.905" width="0.254" layer="21"/>
<smd name="1" x="-2.54" y="1.27" dx="0.6" dy="1.55" layer="1"/>
<smd name="2" x="-1.54" y="1.27" dx="0.6" dy="1.55" layer="1"/>
<smd name="3" x="-0.54" y="1.27" dx="0.6" dy="1.55" layer="1"/>
<smd name="4" x="0.46" y="1.27" dx="0.6" dy="1.55" layer="1"/>
<smd name="5" x="1.46" y="1.27" dx="0.6" dy="1.55" layer="1"/>
<smd name="6" x="2.46" y="1.27" dx="0.6" dy="1.55" layer="1"/>
<smd name="P$1" x="-3.84" y="-0.955" dx="1.2" dy="1.8" layer="1"/>
<smd name="P$2" x="3.76" y="-0.955" dx="1.2" dy="1.8" layer="1"/>
<text x="-1.27" y="2.54" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1X06_NO_SILK">
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="4" x="7.62" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="5" x="10.16" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="6" x="12.7" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="12.446" y1="-0.254" x2="12.954" y2="0.254" layer="51"/>
<rectangle x1="9.906" y1="-0.254" x2="10.414" y2="0.254" layer="51"/>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="MICRO-B-RA-SMT">
<description>Package for an SMT Micro-B connector.  Digikey part #H11613-ND
*** Unproven***</description>
<wire x1="-3.4" y1="-3" x2="3.4" y2="-3" width="0.127" layer="51"/>
<wire x1="-3.4" y1="-3" x2="-3.4" y2="3" width="0.127" layer="51"/>
<wire x1="3.4" y1="3" x2="-3.4" y2="3" width="0.127" layer="51"/>
<wire x1="3.4" y1="3" x2="3.4" y2="-3" width="0.127" layer="51"/>
<smd name="5" x="-1.3" y="-1.95" dx="1.1" dy="0.35" layer="1" rot="R90"/>
<smd name="1" x="1.3" y="-1.95" dx="1.1" dy="0.35" layer="1" rot="R90"/>
<smd name="4" x="-0.65" y="-1.75" dx="1.5" dy="0.35" layer="1" rot="R90"/>
<smd name="3" x="0" y="-1.75" dx="1.5" dy="0.35" layer="1" rot="R90"/>
<smd name="2" x="0.65" y="-1.75" dx="1.5" dy="0.35" layer="1" rot="R90"/>
<text x="-3.6" y="-1.8" size="0.762" layer="25" rot="R90">&gt;NAME</text>
<text x="4.3" y="-1.8" size="0.762" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="MICRO-B-RA-TH">
<description>&lt;h3&gt;Micro B Right Angle through-hole PCB plug connector&lt;/h3&gt;
&lt;b&gt;**Unproven**&lt;/b&gt;&lt;br&gt;
See digikey part #H11673TR-ND</description>
<wire x1="-1.525" y1="0" x2="-1.525" y2="1.55" width="0.127" layer="51"/>
<wire x1="1.525" y1="0" x2="1.525" y2="1.55" width="0.127" layer="51"/>
<wire x1="-1.525" y1="1.55" x2="1.525" y2="1.55" width="0.127" layer="51"/>
<wire x1="-1.525" y1="0" x2="-3.65" y2="0" width="0.127" layer="51"/>
<wire x1="1.525" y1="0" x2="3.65" y2="0" width="0.127" layer="51"/>
<wire x1="-3.65" y1="0" x2="-3.65" y2="-0.95" width="0.127" layer="51"/>
<wire x1="3.65" y1="0" x2="3.65" y2="-0.95" width="0.127" layer="51"/>
<wire x1="-2.5" y1="-3.35" x2="2.5" y2="-3.35" width="0.127" layer="51"/>
<wire x1="-3.65" y1="-0.95" x2="-2.5" y2="-3.35" width="0.127" layer="51"/>
<wire x1="3.65" y1="-0.95" x2="2.5" y2="-3.35" width="0.127" layer="51"/>
<pad name="3" x="0" y="-1.25" drill="0.508" diameter="0.9"/>
<pad name="4" x="0.65" y="0.6" drill="0.508" diameter="0.9"/>
<pad name="2" x="-0.65" y="0.6" drill="0.508" diameter="0.9"/>
<pad name="5" x="1.3" y="-0.95" drill="0.508" diameter="0.9"/>
<pad name="1" x="-1.3" y="-0.95" drill="0.508" diameter="0.9"/>
<text x="-1.651" y="0.635" size="0.381" layer="25" rot="R180">&gt;Name</text>
<text x="1.651" y="0.254" size="0.381" layer="27">&gt;Value</text>
</package>
<package name="MICRO-B-TH">
<description>&lt;h3&gt;Micro B USB Plug Assembly - Straight Through-hole&lt;/h3&gt;
&lt;b&gt;**UNPROVEN**&lt;/b&gt;&lt;Br&gt;
See Digikey part #H11497-ND</description>
<wire x1="-5.125" y1="-2.1" x2="5.125" y2="-2.1" width="0.127" layer="51"/>
<wire x1="-5.125" y1="2.1" x2="5.125" y2="2.1" width="0.127" layer="51"/>
<wire x1="-5.125" y1="-2.1" x2="-5.125" y2="2.1" width="0.127" layer="51"/>
<wire x1="5.125" y1="-2.1" x2="5.125" y2="2.1" width="0.127" layer="51"/>
<pad name="1" x="-1.3" y="-0.775" drill="0.6" diameter="1"/>
<pad name="3" x="0" y="-0.775" drill="0.6" diameter="1"/>
<pad name="5" x="1.3" y="-0.775" drill="0.6" diameter="1"/>
<pad name="4" x="0.65" y="0.775" drill="0.6" diameter="1"/>
<pad name="2" x="-0.65" y="0.775" drill="0.6" diameter="1"/>
<pad name="P$1" x="-4.1" y="0" drill="1.2" rot="R90"/>
<pad name="P$2" x="4.1" y="0" drill="1.2" rot="R90"/>
<text x="-5.08" y="2.286" size="0.381" layer="25">&gt;Name</text>
<text x="-5.08" y="-2.667" size="0.381" layer="27">&gt;Value</text>
</package>
<package name="MICRO-B-SMT">
<description>&lt;h3&gt;USB Micro-B Plug Connector&lt;/h3&gt;
Manufacturer part #: ZX80-B-5SA&lt;br&gt;
Manufacturer: Hirose&lt;br&gt;&lt;br&gt;
&lt;b&gt;***Unproven***&lt;/b&gt; (Passed 1:1 printout test though!)</description>
<wire x1="-9.7" y1="3.77" x2="-8.275" y2="3.77" width="0.127" layer="51"/>
<wire x1="-9.7" y1="0.57" x2="-8.275" y2="0.57" width="0.127" layer="51"/>
<wire x1="-9.7" y1="3.77" x2="-10.275" y2="4.3" width="0.127" layer="51"/>
<wire x1="-10.275" y1="4.3" x2="-10.275" y2="5.38" width="0.127" layer="51"/>
<wire x1="-9.7" y1="0.57" x2="-10.275" y2="0" width="0.127" layer="51"/>
<wire x1="-10.275" y1="0" x2="-10.275" y2="-0.9" width="0.127" layer="51"/>
<wire x1="-8.275" y1="3.77" x2="-8.275" y2="0.57" width="0.127" layer="51" curve="-180"/>
<wire x1="9.7" y1="0.57" x2="8.275" y2="0.57" width="0.127" layer="51"/>
<wire x1="8.275" y1="0.57" x2="8.275" y2="3.77" width="0.127" layer="51" curve="-180"/>
<wire x1="9.7" y1="3.77" x2="8.275" y2="3.77" width="0.127" layer="51"/>
<wire x1="9.7" y1="0.57" x2="10.275" y2="0" width="0.127" layer="51"/>
<wire x1="10.275" y1="0" x2="10.275" y2="-0.9" width="0.127" layer="51"/>
<wire x1="9.7" y1="3.77" x2="10.275" y2="4.4" width="0.127" layer="51"/>
<wire x1="10.275" y1="4.4" x2="10.275" y2="5.38" width="0.127" layer="51"/>
<wire x1="-10.275" y1="5.38" x2="-4.275" y2="5.38" width="0.127" layer="51"/>
<wire x1="10.275" y1="5.38" x2="4.275" y2="5.38" width="0.127" layer="51"/>
<wire x1="-10.275" y1="-0.9" x2="-4.275" y2="-0.9" width="0.127" layer="51"/>
<wire x1="10.275" y1="-0.9" x2="4.275" y2="-0.9" width="0.127" layer="51"/>
<wire x1="-4.275" y1="-0.9" x2="-4.275" y2="0" width="0.127" layer="51"/>
<wire x1="4.275" y1="-0.9" x2="4.275" y2="0" width="0.127" layer="51"/>
<wire x1="-4.275" y1="0" x2="4.275" y2="0" width="0.127" layer="51"/>
<wire x1="-4.275" y1="5.38" x2="-4.275" y2="4.48" width="0.127" layer="51"/>
<wire x1="4.275" y1="5.38" x2="4.275" y2="4.48" width="0.127" layer="51"/>
<wire x1="-4.275" y1="4.48" x2="4.275" y2="4.48" width="0.127" layer="51"/>
<pad name="P$6" x="-3.325" y="3.15" drill="1.3" diameter="2.2" rot="R90"/>
<pad name="P$7" x="-3.325" y="0" drill="1.3" diameter="2.2" rot="R90"/>
<pad name="P$8" x="3.325" y="3.15" drill="1.3" diameter="2.2" rot="R90"/>
<pad name="P$9" x="3.325" y="0" drill="1.3" diameter="2.2" rot="R90"/>
<smd name="3" x="0" y="0" dx="2.2" dy="0.4" layer="1" rot="R90"/>
<smd name="2" x="-0.65" y="0" dx="2.2" dy="0.4" layer="1" rot="R90"/>
<smd name="1" x="-1.3" y="0" dx="2.2" dy="0.4" layer="1" rot="R90"/>
<smd name="5" x="1.3" y="0" dx="2.2" dy="0.4" layer="1" rot="R90"/>
<smd name="4" x="0.65" y="0" dx="2.2" dy="0.4" layer="1" rot="R90"/>
<text x="-10.29" y="5.58" size="0.4064" layer="25">&gt;Name</text>
<text x="10.39" y="5.988" size="0.4064" layer="27" rot="R180">&gt;Value</text>
<hole x="-8.275" y="2.17" drill="3.3"/>
<hole x="8.275" y="2.17" drill="3.3"/>
</package>
<package name="USB-B-MICRO-SMD_V03">
<text x="-4.66" y="5.96" size="0.3048" layer="51">PCB Front</text>
<wire x1="-3" y1="5.6" x2="-2.3" y2="5.3" width="0.08" layer="51"/>
<wire x1="-2.3" y1="5.3" x2="-2.4" y2="5.5" width="0.08" layer="51"/>
<wire x1="-2.3" y1="5.3" x2="-2.5" y2="5.2" width="0.08" layer="51"/>
<text x="-1.27" y="5.969" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="5.461" size="0.4064" layer="27">&gt;VALUE</text>
<smd name="D+1" x="2.725" y="0" dx="0.4" dy="1.45" layer="1" rot="R90"/>
<smd name="D-1" x="2.725" y="0.65" dx="0.4" dy="1.45" layer="1" rot="R90"/>
<smd name="VBUS1" x="2.725" y="1.3" dx="0.4" dy="1.45" layer="1" rot="R90"/>
<smd name="ID1" x="2.725" y="-0.65" dx="0.4" dy="1.45" layer="1" rot="R90"/>
<smd name="GND1" x="2.725" y="-1.3" dx="0.4" dy="1.45" layer="1" rot="R90"/>
<hole x="2.2" y="1.9" drill="0.85"/>
<hole x="2.2" y="-1.9" drill="0.85"/>
<rectangle x1="-0.75" y1="2.784" x2="0.75" y2="4.584" layer="31"/>
<rectangle x1="-0.35" y1="-0.75" x2="0.35" y2="0.75" layer="31"/>
<rectangle x1="-0.75" y1="-4.584" x2="0.75" y2="-2.784" layer="31"/>
<wire x1="-2.15" y1="3.9" x2="-2.15" y2="-3.9" width="0.127" layer="49"/>
<wire x1="2.85" y1="3.9" x2="2.85" y2="-3.9" width="0.127" layer="49"/>
<wire x1="2.85" y1="3.9" x2="-2.15" y2="3.9" width="0.127" layer="49"/>
<wire x1="2.85" y1="-3.9" x2="-2.15" y2="-3.9" width="0.127" layer="49"/>
<wire x1="2.981959375" y1="3.99288125" x2="2" y2="3.99288125" width="0.3048" layer="21"/>
<wire x1="2" y1="3.99288125" x2="2" y2="4" width="0.3048" layer="21"/>
<wire x1="3" y1="4" x2="3" y2="3" width="0.3048" layer="21"/>
<wire x1="2" y1="-4" x2="3" y2="-4" width="0.3048" layer="21"/>
<wire x1="3" y1="-4" x2="3" y2="-3" width="0.3048" layer="21"/>
<wire x1="-1" y1="4" x2="-2" y2="4" width="0.3048" layer="21"/>
<wire x1="-1" y1="-4" x2="-2" y2="-4" width="0.3048" layer="21"/>
<rectangle x1="-0.85" y1="2.684" x2="0.85" y2="4.684" layer="29"/>
<rectangle x1="-0.85" y1="-4.684" x2="0.85" y2="-2.684" layer="29"/>
<rectangle x1="-0.85" y1="-1.35" x2="0.85" y2="1.35" layer="29"/>
<smd name="SHIELD1" x="0" y="3.685" dx="1.8" dy="1.5" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="SHIELD3" x="0" y="0" dx="2.5" dy="1.5" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="SHIELD2" x="0" y="-3.685" dx="1.8" dy="1.5" layer="1" rot="R90" stop="no" cream="no"/>
<wire x1="-2" y1="7" x2="-2" y2="0" width="0" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="M06">
<wire x1="1.27" y1="-7.62" x2="-5.08" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="-2.54" x2="0" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="-5.08" x2="0" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="-5.08" y1="10.16" x2="-5.08" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-7.62" x2="1.27" y2="10.16" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="10.16" x2="1.27" y2="10.16" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="5.08" x2="0" y2="5.08" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="2.54" x2="0" y2="2.54" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="7.62" x2="0" y2="7.62" width="0.6096" layer="94"/>
<text x="-5.08" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<text x="-5.08" y="10.922" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="5.08" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="5.08" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="5.08" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="4" x="5.08" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="5.08" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="6" x="5.08" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
<symbol name="MICROB-PLUG">
<wire x1="-5.08" y1="7.62" x2="-5.08" y2="-7.62" width="0.508" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="5.08" y2="-7.62" width="0.508" layer="94"/>
<wire x1="5.08" y1="-7.62" x2="5.08" y2="7.62" width="0.508" layer="94"/>
<wire x1="5.08" y1="7.62" x2="-5.08" y2="7.62" width="0.508" layer="94"/>
<text x="-4.826" y="8.128" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-9.906" size="1.778" layer="96">&gt;VALUE</text>
<pin name="VCC" x="-7.62" y="5.08" length="short"/>
<pin name="D-" x="-7.62" y="2.54" length="short"/>
<pin name="D+" x="-7.62" y="0" length="short"/>
<pin name="ID" x="-7.62" y="-2.54" length="short"/>
<pin name="GND" x="-7.62" y="-5.08" length="short"/>
<pin name="SHIELD" x="7.62" y="0" visible="off" length="short" rot="R180"/>
<text x="4.064" y="0" size="0.8128" layer="95" rot="R90" align="bottom-center">SHIELD</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="M06" prefix="JP" uservalue="yes">
<description>&lt;b&gt;Header 6&lt;/b&gt;&lt;br&gt;
Standard 6-pin 0.1" header. Use with straight break away headers (SKU : PRT-00116), right angle break away headers (PRT-00553), swiss pins (PRT-00743), machine pins (PRT-00117), and female headers (PRT-00115). Molex polarized connector foot print use with SKU : PRT-08094 with associated crimp pins and housings.&lt;p&gt;



NOTES ON THE VARIANTS LOCK and LOCK_LONGPADS...
This footprint was designed to help hold the alignment of a through-hole component (i.e.  6-pin header) while soldering it into place. You may notice that each hole has been shifted either up or down by 0.005 of an inch from it's more standard position (which is a perfectly straight line).  This slight alteration caused the pins (the squares in the middle) to touch the edges of the holes.  Because they are alternating, it causes a "brace" to hold the component in place.  0.005 has proven to be the perfect amount of "off-center" position when using our standard breakaway headers. Although looks a little odd when you look at the bare footprint, once you have a header in there, the alteration is very hard to notice.  Also,if you push a header all the way into place, it is covered up entirely on the bottom side.  This idea of altering the position of holes to aid alignment 
will be further integrated into the Sparkfun Library for other footprints.  It can help hold any component with 3 or more connection pins.</description>
<gates>
<gate name="G$1" symbol="M06" x="-2.54" y="0"/>
</gates>
<devices>
<device name="SILK_FEMALE_PTH" package="1X06">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-08437"/>
</technology>
</technologies>
</device>
<device name="POLAR" package="MOLEX-1X6">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="RA" package="MOLEX-1X6-RA">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="1X06-SMD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-08971" constant="no"/>
<attribute name="VALUE" value="RA 6Pin SMD" constant="no"/>
</technology>
</technologies>
</device>
<device name="LOCK" package="1X06_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="LOCK_LONGPADS" package="1X06_LOCK_LONGPADS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="POLAR_LOCK" package="MOLEX-1X6_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="RA_LOCK" package="MOLEX-1X6-RA_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SIP_LOCK" package="1X06-SIP_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="FEMALE_LOCK" package="1X06_FEMALE_LOCK.010">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="LONGPADS" package="1X06_LONGPADS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1X06-SMD_EDGE_FEMALE" package="1X06-SMD_EDGE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3.5MM-6" package="SCREWTERMINAL-3.5MM-6">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMDF" package="1X06-SMD-FEMALE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD-FEMALE-V2" package="1X06-SMD-FEMALE-V2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="POGOPIN_HOLES_ONLY" package="1X06_HOLES_ONLY">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-08437"/>
</technology>
</technologies>
</device>
<device name="SMD-STRAIGHT-FEMALE" package="1X06_SMD_STRAIGHT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-10203"/>
</technology>
</technologies>
</device>
<device name="SMD-STRAIGHT-ALT-FEMALE" package="1X06_SMD_STRAIGHT_ALT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-10203"/>
</technology>
</technologies>
</device>
<device name="SMD-STRAIGHT-COMBO-FEMALE" package="1X06_SMD_STRAIGHT_COMBO">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-10203"/>
</technology>
</technologies>
</device>
<device name="VERNIER-ANALOG" package="BTA">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="VERNIER-DIGITAL" package="BTD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD_MALE" package="1X06_SMD_MALE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-11293"/>
</technology>
</technologies>
</device>
<device name="SMD-1MM" package="1X06-1MM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="NO_SILK_FEMALE_PTH" package="1X06_NO_SILK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-08437"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="USB_MICROB_PLUG" prefix="JP" uservalue="yes">
<description>USB Micro-B connectors&lt;br&gt;
Some male, some female. Watch your step!</description>
<gates>
<gate name="G$1" symbol="MICROB-PLUG" x="0" y="0"/>
</gates>
<devices>
<device name="&quot;" package="MICRO-B-RA-SMT">
<connects>
<connect gate="G$1" pin="D+" pad="3"/>
<connect gate="G$1" pin="D-" pad="2"/>
<connect gate="G$1" pin="GND" pad="5"/>
<connect gate="G$1" pin="ID" pad="4"/>
<connect gate="G$1" pin="VCC" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-PTH" package="MICRO-B-RA-TH">
<connects>
<connect gate="G$1" pin="D+" pad="3"/>
<connect gate="G$1" pin="D-" pad="2"/>
<connect gate="G$1" pin="GND" pad="5"/>
<connect gate="G$1" pin="ID" pad="4"/>
<connect gate="G$1" pin="VCC" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-PTH2" package="MICRO-B-TH">
<connects>
<connect gate="G$1" pin="D+" pad="3"/>
<connect gate="G$1" pin="D-" pad="2"/>
<connect gate="G$1" pin="GND" pad="5"/>
<connect gate="G$1" pin="ID" pad="4"/>
<connect gate="G$1" pin="VCC" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-SMT" package="MICRO-B-SMT">
<connects>
<connect gate="G$1" pin="D+" pad="3"/>
<connect gate="G$1" pin="D-" pad="2"/>
<connect gate="G$1" pin="GND" pad="5"/>
<connect gate="G$1" pin="ID" pad="4"/>
<connect gate="G$1" pin="VCC" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CONN-11752" package="USB-B-MICRO-SMD_V03">
<connects>
<connect gate="G$1" pin="D+" pad="D+1"/>
<connect gate="G$1" pin="D-" pad="D-1"/>
<connect gate="G$1" pin="GND" pad="GND1"/>
<connect gate="G$1" pin="ID" pad="ID1"/>
<connect gate="G$1" pin="SHIELD" pad="SHIELD1 SHIELD2 SHIELD3"/>
<connect gate="G$1" pin="VCC" pad="VBUS1"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-11752" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Resistors">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find resistors, capacitors, inductors, test points, jumper pads, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="1206">
<wire x1="-2.473" y1="0.983" x2="2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-0.983" x2="-2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-0.983" x2="-2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="0.983" x2="2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-0.965" y1="0.787" x2="0.965" y2="0.787" width="0.1016" layer="51"/>
<wire x1="-0.965" y1="-0.787" x2="0.965" y2="-0.787" width="0.1016" layer="51"/>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<text x="-1.27" y="1.143" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.397" y="-1.524" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-1.7018" y1="-0.8509" x2="-0.9517" y2="0.8491" layer="51"/>
<rectangle x1="0.9517" y1="-0.8491" x2="1.7018" y2="0.8509" layer="51"/>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
</package>
<package name="AXIAL-0.3">
<wire x1="-2.54" y1="0.762" x2="2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0.762" x2="2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-0.762" x2="-2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="-3.81" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="3.81" y="0" drill="0.9" diameter="1.8796"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25" font="vector">&gt;Name</text>
<text x="-2.032" y="-0.381" size="1.016" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="R2010">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-1.662" y1="1.245" x2="1.662" y2="1.245" width="0.1524" layer="51"/>
<wire x1="-1.637" y1="-1.245" x2="1.687" y2="-1.245" width="0.1524" layer="51"/>
<wire x1="-3.473" y1="1.483" x2="3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="1.483" x2="3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="-1.483" x2="-3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="-3.473" y1="-1.483" x2="-3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="-1.027" y1="1.245" x2="1.027" y2="1.245" width="0.1524" layer="21"/>
<wire x1="-1.002" y1="-1.245" x2="1.016" y2="-1.245" width="0.1524" layer="21"/>
<smd name="1" x="-2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<smd name="2" x="2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<text x="-2.54" y="1.5875" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.54" y="-2.032" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-2.4892" y1="-1.3208" x2="-1.6393" y2="1.3292" layer="51"/>
<rectangle x1="1.651" y1="-1.3208" x2="2.5009" y2="1.3292" layer="51"/>
</package>
<package name="0805">
<wire x1="-0.3" y1="0.6" x2="0.3" y2="0.6" width="0.1524" layer="21"/>
<wire x1="-0.3" y1="-0.6" x2="0.3" y2="-0.6" width="0.1524" layer="21"/>
<smd name="1" x="-0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<smd name="2" x="0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<text x="-0.762" y="0.8255" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="0603-RES">
<wire x1="-1.473" y1="0.983" x2="1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.983" x2="1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.983" x2="-1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.983" x2="-1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="-0.889" y="0.762" size="0.4064" layer="25" font="vector">&gt;NAME</text>
<text x="-1.016" y="-1.143" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
<rectangle x1="-0.2286" y1="-0.381" x2="0.2286" y2="0.381" layer="21"/>
</package>
<package name="1/6W-RES">
<description>1/6W Thru-hole Resistor - *UNPROVEN*</description>
<wire x1="-1.55" y1="0.85" x2="-1.55" y2="-0.85" width="0.2032" layer="21"/>
<wire x1="-1.55" y1="-0.85" x2="1.55" y2="-0.85" width="0.2032" layer="21"/>
<wire x1="1.55" y1="-0.85" x2="1.55" y2="0.85" width="0.2032" layer="21"/>
<wire x1="1.55" y1="0.85" x2="-1.55" y2="0.85" width="0.2032" layer="21"/>
<pad name="1" x="-2.5" y="0" drill="0.762" diameter="1.6764"/>
<pad name="2" x="2.5" y="0" drill="0.762" diameter="1.6764"/>
<text x="-1.2662" y="0.9552" size="0.6096" layer="25">&gt;NAME</text>
<text x="-1.423" y="-0.4286" size="0.8128" layer="21" ratio="15">&gt;VALUE</text>
</package>
<package name="R2512">
<wire x1="-2.362" y1="1.473" x2="2.387" y2="1.473" width="0.1524" layer="51"/>
<wire x1="-2.362" y1="-1.473" x2="2.387" y2="-1.473" width="0.1524" layer="51"/>
<smd name="1" x="-2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<smd name="2" x="2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<text x="-2.54" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-3.2004" y1="-1.5494" x2="-2.3505" y2="1.5507" layer="51"/>
<rectangle x1="2.3622" y1="-1.5494" x2="3.2121" y2="1.5507" layer="51"/>
</package>
<package name="AXIAL-0.4">
<description>1/4W Resistor, 0.4" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-3.15" y1="-1.2" x2="-3.15" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-3.15" y1="1.2" x2="3.15" y2="1.2" width="0.2032" layer="21"/>
<wire x1="3.15" y1="1.2" x2="3.15" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="3.15" y1="-1.2" x2="-3.15" y2="-1.2" width="0.2032" layer="21"/>
<pad name="P$1" x="-5.08" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="5.08" y="0" drill="0.9" diameter="1.8796"/>
<text x="-3.175" y="1.905" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-2.286" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.5">
<description>1/2W Resistor, 0.5" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-4.5" y1="-1.65" x2="-4.5" y2="1.65" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="1.65" x2="4.5" y2="1.65" width="0.2032" layer="21"/>
<wire x1="4.5" y1="1.65" x2="4.5" y2="-1.65" width="0.2032" layer="21"/>
<wire x1="4.5" y1="-1.65" x2="-4.5" y2="-1.65" width="0.2032" layer="21"/>
<pad name="P$1" x="-6.35" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="6.35" y="0" drill="0.9" diameter="1.8796"/>
<text x="-4.445" y="2.54" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-3.429" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.6">
<description>1W Resistor, 0.6" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-5.75" y1="-2.25" x2="-5.75" y2="2.25" width="0.2032" layer="21"/>
<wire x1="-5.75" y1="2.25" x2="5.75" y2="2.25" width="0.2032" layer="21"/>
<wire x1="5.75" y1="2.25" x2="5.75" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="5.75" y1="-2.25" x2="-5.75" y2="-2.25" width="0.2032" layer="21"/>
<pad name="P$1" x="-7.62" y="0" drill="1.2" diameter="1.8796"/>
<pad name="P$2" x="7.62" y="0" drill="1.2" diameter="1.8796"/>
<text x="-5.715" y="3.175" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-4.064" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.8">
<description>2W Resistor, 0.8" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-7.75" y1="-2.5" x2="-7.75" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-7.75" y1="2.5" x2="7.75" y2="2.5" width="0.2032" layer="21"/>
<wire x1="7.75" y1="2.5" x2="7.75" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="7.75" y1="-2.5" x2="-7.75" y2="-2.5" width="0.2032" layer="21"/>
<pad name="P$1" x="-10.16" y="0" drill="1.2" diameter="1.8796"/>
<pad name="P$2" x="10.16" y="0" drill="1.2" diameter="1.8796"/>
<text x="-7.62" y="3.175" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-5.969" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.3-KIT">
<description>&lt;h3&gt;AXIAL-0.3-KIT&lt;/h3&gt;

Commonly used for 1/4W through-hole resistors. 0.3" pitch between holes.&lt;br&gt;
&lt;br&gt;

&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of the AXIAL-0.3 package. This package has a smaller diameter top stop mask, which doesn't cover the diameter of the pad. This means only the bottom side of the pads' copper will be exposed. You'll only be able to solder to the bottom side.</description>
<wire x1="-2.54" y1="1.27" x2="2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="0" width="0.254" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="-1.27" x2="-2.54" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="0" width="0.254" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.254" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.254" layer="21"/>
<pad name="P$1" x="-3.81" y="0" drill="1.016" diameter="2.032" stop="no"/>
<pad name="P$2" x="3.81" y="0" drill="1.016" diameter="2.032" stop="no"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25" font="vector">&gt;Name</text>
<text x="-2.159" y="-0.762" size="1.27" layer="21" font="vector" ratio="15">&gt;Value</text>
<polygon width="0.127" layer="30">
<vertex x="3.8201" y="-0.9449" curve="-90"/>
<vertex x="2.8652" y="-0.0152" curve="-90.011749"/>
<vertex x="3.8176" y="0.9602" curve="-90"/>
<vertex x="4.7676" y="-0.0178" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="3.8176" y="-0.4369" curve="-90.012891"/>
<vertex x="3.3731" y="-0.0127" curve="-90"/>
<vertex x="3.8176" y="0.4546" curve="-90"/>
<vertex x="4.2595" y="-0.0025" curve="-90.012967"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="-3.8075" y="-0.9525" curve="-90"/>
<vertex x="-4.7624" y="-0.0228" curve="-90.011749"/>
<vertex x="-3.81" y="0.9526" curve="-90"/>
<vertex x="-2.86" y="-0.0254" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-3.81" y="-0.4445" curve="-90.012891"/>
<vertex x="-4.2545" y="-0.0203" curve="-90"/>
<vertex x="-3.81" y="0.447" curve="-90"/>
<vertex x="-3.3681" y="-0.0101" curve="-90.012967"/>
</polygon>
</package>
<package name="AXIAL-0.3EZ">
<description>This is the "EZ" version of the standard .3" spaced resistor package.&lt;br&gt;
It has a reduced top mask to make it harder to install upside-down.</description>
<wire x1="-2.54" y1="0.762" x2="2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0.762" x2="2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-0.762" x2="-2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="-3.81" y="0" drill="0.9" diameter="1.8796" stop="no"/>
<pad name="P$2" x="3.81" y="0" drill="0.9" diameter="1.8796" stop="no"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25" font="vector">&gt;Name</text>
<text x="-2.032" y="-0.381" size="1.016" layer="21" font="vector" ratio="15">&gt;Value</text>
<circle x="-3.81" y="0" radius="0.508" width="0" layer="29"/>
<circle x="3.81" y="0" radius="0.523634375" width="0" layer="29"/>
<circle x="-3.81" y="0" radius="1.02390625" width="0" layer="30"/>
<circle x="3.81" y="0" radius="1.04726875" width="0" layer="30"/>
</package>
<package name="AXIAL-0.1EZ">
<wire x1="1.27" y1="-0.762" x2="1.27" y2="0" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0" x2="1.27" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.524" y1="0" x2="1.27" y2="0" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0" x2="1.016" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="0" y="0" drill="0.9" diameter="1.8796" stop="no"/>
<pad name="P$2" x="2.54" y="0" drill="0.9" diameter="1.8796" stop="no"/>
<text x="0" y="1.27" size="1.016" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="0" y="-2.159" size="1.016" layer="21" font="vector" ratio="15">&gt;Value</text>
<circle x="0" y="0" radius="0.4572" width="0" layer="29"/>
<circle x="0" y="0" radius="1.016" width="0" layer="30"/>
<circle x="2.54" y="0" radius="1.016" width="0" layer="30"/>
<circle x="0" y="0" radius="0.4572" width="0" layer="29"/>
<circle x="2.54" y="0" radius="0.4572" width="0" layer="29"/>
</package>
<package name="AXIAL-0.1">
<wire x1="1.27" y1="-0.762" x2="1.27" y2="0" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0" x2="1.27" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.524" y1="0" x2="1.27" y2="0" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0" x2="1.016" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="0" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="2.54" y="0" drill="0.9" diameter="1.8796"/>
<text x="0" y="1.27" size="1.016" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="0" y="-2.159" size="1.016" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="0402-RES">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.483" x2="1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.483" x2="1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.483" x2="-1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.483" x2="-1.473" y2="0.483" width="0.0508" layer="39"/>
<smd name="1" x="-0.58" y="0" dx="0.85" dy="0.9" layer="1"/>
<smd name="2" x="0.58" y="0" dx="0.85" dy="0.9" layer="1"/>
<text x="-0.889" y="0.6985" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.0795" y="-1.143" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
<rectangle x1="-0.2032" y1="-0.3556" x2="0.2032" y2="0.3556" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="RESISTOR">
<wire x1="-2.54" y1="0" x2="-2.159" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-2.159" y1="1.016" x2="-1.524" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-1.524" y1="-1.016" x2="-0.889" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-0.889" y1="1.016" x2="-0.254" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-0.254" y1="-1.016" x2="0.381" y2="1.016" width="0.1524" layer="94"/>
<wire x1="0.381" y1="1.016" x2="1.016" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-1.016" x2="1.651" y2="1.016" width="0.1524" layer="94"/>
<wire x1="1.651" y1="1.016" x2="2.286" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="2.286" y1="-1.016" x2="2.54" y2="0" width="0.1524" layer="94"/>
<text x="-3.81" y="1.4986" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="RESISTOR" prefix="R" uservalue="yes">
<description>&lt;b&gt;Resistor&lt;/b&gt;
Basic schematic elements and footprints for 0603, 1206, and PTH resistors.</description>
<gates>
<gate name="G$1" symbol="RESISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="AXIAL-0.3" package="AXIAL-0.3">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2010" package="R2010">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805-RES" package="0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603-RES" package="0603-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603" package="0603-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/6W" package="1/6W-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2512" package="R2512">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/4W" package="AXIAL-0.4">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/2W" package="AXIAL-0.5">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1W" package="AXIAL-0.6">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-2W" package="AXIAL-0.8">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="KIT" package="AXIAL-0.3-KIT">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="EZ" package="AXIAL-0.3EZ">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/4W-VERT-KIT" package="AXIAL-0.1EZ">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/4W-VERT" package="AXIAL-0.1">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0402" package="0402-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="inductors">
<description>&lt;b&gt;Inductors and Filters&lt;/b&gt;&lt;p&gt;
Based on the previous library ind-a.lbr&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="0402">
<description>&lt;b&gt;EMIFIL (R) Chip Ferrite Bead for GHz Noise&lt;/b&gt;&lt;p&gt;
Source: http://www.murata.com/ Ferrite Bead BLM15H.pdf</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.483" x2="1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.483" x2="1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.483" x2="-1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.483" x2="-1.473" y2="0.483" width="0.0508" layer="39"/>
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-0.635" y="0.635" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-1.905" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
</package>
</packages>
<symbols>
<symbol name="L">
<text x="-3.81" y="1.3716" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-2.921" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.54" y1="-0.889" x2="2.54" y2="0.889" layer="94"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="BLM15H" prefix="L">
<description>&lt;b&gt;EMIFIL (R) Chip Ferrite Bead for GHz Noise&lt;/b&gt;&lt;p&gt;
Source: http://www.murata.com/ Ferrite Bead BLM15H.pdf</description>
<gates>
<gate name="G$1" symbol="L" x="0" y="0"/>
</gates>
<devices>
<device name="" package="0402">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="B121SN1"/>
<technology name="B221SN1"/>
<technology name="D102SN1"/>
<technology name="D182SN1"/>
<technology name="D601SN1"/>
<technology name="G102SN1"/>
<technology name="G601SN1"/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Electromechanical">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find anything that moves- switches, relays, buttons, potentiometers. Also, anything that goes on a board but isn't electrical in nature- screws, standoffs, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="TACTILE-PTH">
<description>&lt;b&gt;OMRON SWITCH&lt;/b&gt;</description>
<wire x1="3.048" y1="1.016" x2="3.048" y2="2.54" width="0.2032" layer="51"/>
<wire x1="3.048" y1="2.54" x2="2.54" y2="3.048" width="0.2032" layer="51"/>
<wire x1="2.54" y1="-3.048" x2="3.048" y2="-2.54" width="0.2032" layer="51"/>
<wire x1="3.048" y1="-2.54" x2="3.048" y2="-1.016" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="3.048" x2="-3.048" y2="2.54" width="0.2032" layer="51"/>
<wire x1="-3.048" y1="2.54" x2="-3.048" y2="1.016" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="-3.048" x2="-3.048" y2="-2.54" width="0.2032" layer="51"/>
<wire x1="-3.048" y1="-2.54" x2="-3.048" y2="-1.016" width="0.2032" layer="51"/>
<wire x1="2.54" y1="-3.048" x2="2.159" y2="-3.048" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="-3.048" x2="-2.159" y2="-3.048" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="3.048" x2="-2.159" y2="3.048" width="0.2032" layer="51"/>
<wire x1="2.54" y1="3.048" x2="2.159" y2="3.048" width="0.2032" layer="51"/>
<wire x1="2.159" y1="3.048" x2="-2.159" y2="3.048" width="0.2032" layer="21"/>
<wire x1="-2.159" y1="-3.048" x2="2.159" y2="-3.048" width="0.2032" layer="21"/>
<wire x1="3.048" y1="0.998" x2="3.048" y2="-1.016" width="0.2032" layer="21"/>
<wire x1="-3.048" y1="1.028" x2="-3.048" y2="-1.016" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="0.508" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="-0.508" x2="-2.54" y2="-1.27" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="0.508" x2="-2.159" y2="-0.381" width="0.2032" layer="51"/>
<circle x="0" y="0" radius="1.778" width="0.2032" layer="21"/>
<pad name="1" x="-3.2512" y="2.2606" drill="1.016" diameter="1.8796"/>
<pad name="2" x="3.2512" y="2.2606" drill="1.016" diameter="1.8796"/>
<pad name="3" x="-3.2512" y="-2.2606" drill="1.016" diameter="1.8796"/>
<pad name="4" x="3.2512" y="-2.2606" drill="1.016" diameter="1.8796"/>
<text x="-2.54" y="3.81" size="1.27" layer="25" ratio="10">&gt;NAME</text>
</package>
<package name="TACTILE_SWITCH_SMD-2">
<wire x1="1.905" y1="1.27" x2="1.905" y2="0.445" width="0.127" layer="51"/>
<wire x1="1.905" y1="0.445" x2="2.16" y2="-0.01" width="0.127" layer="51"/>
<wire x1="1.905" y1="-0.23" x2="1.905" y2="-1.115" width="0.127" layer="51"/>
<wire x1="-2.25" y1="2.25" x2="2.25" y2="2.25" width="0.127" layer="51"/>
<wire x1="2.25" y1="2.25" x2="2.25" y2="-2.25" width="0.127" layer="51"/>
<wire x1="2.25" y1="-2.25" x2="-2.25" y2="-2.25" width="0.127" layer="51"/>
<wire x1="-2.25" y1="-2.25" x2="-2.25" y2="2.25" width="0.127" layer="51"/>
<wire x1="-2.2" y1="0.8" x2="-2.2" y2="-0.8" width="0.2032" layer="21"/>
<wire x1="1.3" y1="2.2" x2="-1.3" y2="2.2" width="0.2032" layer="21"/>
<wire x1="2.2" y1="-0.8" x2="2.2" y2="0.8" width="0.2032" layer="21"/>
<wire x1="-1.3" y1="-2.2" x2="1.3" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="2.2" y1="0.8" x2="1.8" y2="0.8" width="0.2032" layer="21"/>
<wire x1="2.2" y1="-0.8" x2="1.8" y2="-0.8" width="0.2032" layer="21"/>
<wire x1="-1.8" y1="0.8" x2="-2.2" y2="0.8" width="0.2032" layer="21"/>
<wire x1="-1.8" y1="-0.8" x2="-2.2" y2="-0.8" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="1.27" width="0.2032" layer="21"/>
<smd name="1" x="2.225" y="1.75" dx="1.1" dy="0.7" layer="1" rot="R90"/>
<smd name="2" x="2.225" y="-1.75" dx="1.1" dy="0.7" layer="1" rot="R90"/>
<smd name="3" x="-2.225" y="-1.75" dx="1.1" dy="0.7" layer="1" rot="R90"/>
<smd name="4" x="-2.225" y="1.75" dx="1.1" dy="0.7" layer="1" rot="R90"/>
<text x="-0.889" y="1.778" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.889" y="-2.032" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="TACTILE-PTH-12MM">
<wire x1="5" y1="-1.3" x2="5" y2="-0.7" width="0.2032" layer="51"/>
<wire x1="5" y1="-0.7" x2="4.5" y2="-0.2" width="0.2032" layer="51"/>
<wire x1="5" y1="0.2" x2="5" y2="1" width="0.2032" layer="51"/>
<wire x1="-6" y1="4" x2="-6" y2="5" width="0.2032" layer="21"/>
<wire x1="-5" y1="6" x2="5" y2="6" width="0.2032" layer="21"/>
<wire x1="6" y1="5" x2="6" y2="4" width="0.2032" layer="21"/>
<wire x1="6" y1="1" x2="6" y2="-1" width="0.2032" layer="21"/>
<wire x1="6" y1="-4" x2="6" y2="-5" width="0.2032" layer="21"/>
<wire x1="5" y1="-6" x2="-5" y2="-6" width="0.2032" layer="21"/>
<wire x1="-6" y1="-5" x2="-6" y2="-4" width="0.2032" layer="21"/>
<wire x1="-6" y1="-1" x2="-6" y2="1" width="0.2032" layer="21"/>
<wire x1="-6" y1="5" x2="-5" y2="6" width="0.2032" layer="21" curve="-90"/>
<wire x1="5" y1="6" x2="6" y2="5" width="0.2032" layer="21" curve="-90"/>
<wire x1="6" y1="-5" x2="5" y2="-6" width="0.2032" layer="21" curve="-90"/>
<wire x1="-5" y1="-6" x2="-6" y2="-5" width="0.2032" layer="21" curve="-90"/>
<circle x="0" y="0" radius="3.5" width="0.2032" layer="21"/>
<circle x="-4.5" y="4.5" radius="0.3" width="0.7" layer="21"/>
<circle x="4.5" y="4.5" radius="0.3" width="0.7" layer="21"/>
<circle x="4.5" y="-4.5" radius="0.3" width="0.7" layer="21"/>
<circle x="-4.5" y="-4.5" radius="0.3" width="0.7" layer="21"/>
<pad name="4" x="-6.25" y="2.5" drill="1.2" diameter="2.159"/>
<pad name="2" x="-6.25" y="-2.5" drill="1.2" diameter="2.159"/>
<pad name="1" x="6.25" y="-2.5" drill="1.2" diameter="2.159"/>
<pad name="3" x="6.25" y="2.5" drill="1.2" diameter="2.159"/>
</package>
<package name="TACTILE-SWITCH-1101NE">
<description>SparkFun SKU# COM-08229</description>
<wire x1="-3" y1="1.1" x2="-3" y2="-1.1" width="0.127" layer="51"/>
<wire x1="3" y1="1.1" x2="3" y2="-1.1" width="0.127" layer="51"/>
<wire x1="-2.75" y1="1.75" x2="-3" y2="1.5" width="0.2032" layer="21" curve="90"/>
<wire x1="-2.75" y1="1.75" x2="2.75" y2="1.75" width="0.2032" layer="21"/>
<wire x1="2.75" y1="1.75" x2="3" y2="1.5" width="0.2032" layer="21" curve="-90"/>
<wire x1="3" y1="-1.5" x2="2.75" y2="-1.75" width="0.2032" layer="21" curve="-90"/>
<wire x1="2.75" y1="-1.75" x2="-2.75" y2="-1.75" width="0.2032" layer="21"/>
<wire x1="-3" y1="-1.5" x2="-2.75" y2="-1.75" width="0.2032" layer="21" curve="90"/>
<wire x1="-3" y1="-1.5" x2="-3" y2="-1.1" width="0.2032" layer="21"/>
<wire x1="-3" y1="1.1" x2="-3" y2="1.5" width="0.2032" layer="21"/>
<wire x1="3" y1="1.1" x2="3" y2="1.5" width="0.2032" layer="21"/>
<wire x1="3" y1="-1.5" x2="3" y2="-1.1" width="0.2032" layer="21"/>
<wire x1="-1.5" y1="0.75" x2="1.5" y2="0.75" width="0.2032" layer="21"/>
<wire x1="1.5" y1="-0.75" x2="-1.5" y2="-0.75" width="0.2032" layer="21"/>
<wire x1="-1.5" y1="-0.75" x2="-1.5" y2="0.75" width="0.2032" layer="21"/>
<wire x1="1.5" y1="-0.75" x2="1.5" y2="0.75" width="0.2032" layer="21"/>
<wire x1="-2" y1="0" x2="-1" y2="0" width="0.127" layer="51"/>
<wire x1="-1" y1="0" x2="0.1" y2="0.5" width="0.127" layer="51"/>
<wire x1="0.3" y1="0" x2="2" y2="0" width="0.127" layer="51"/>
<smd name="1" x="-3.15" y="0" dx="2.3" dy="1.6" layer="1" rot="R180"/>
<smd name="2" x="3.15" y="0" dx="2.3" dy="1.6" layer="1" rot="R180"/>
<text x="-3" y="2" size="0.762" layer="25">&gt;NAME</text>
<text x="-3" y="-2.7" size="0.762" layer="27">&gt;VALUE</text>
</package>
<package name="REED_SWITCH_PTH">
<wire x1="-6.985" y1="-0.635" x2="6.985" y2="-0.635" width="0.127" layer="21"/>
<wire x1="-6.985" y1="-0.635" x2="-6.985" y2="0" width="0.127" layer="21"/>
<wire x1="-6.985" y1="0" x2="-6.985" y2="0.635" width="0.127" layer="21"/>
<wire x1="-6.985" y1="0.635" x2="6.985" y2="0.635" width="0.127" layer="21"/>
<wire x1="6.985" y1="0.635" x2="6.985" y2="0" width="0.127" layer="21"/>
<wire x1="6.985" y1="0" x2="6.985" y2="-0.635" width="0.127" layer="21"/>
<wire x1="-6.985" y1="0" x2="-7.62" y2="0" width="0.127" layer="21"/>
<wire x1="6.985" y1="0" x2="7.62" y2="0" width="0.127" layer="21"/>
<pad name="P$1" x="-8.89" y="0" drill="1.016" diameter="1.8796"/>
<pad name="P$2" x="8.89" y="0" drill="1.016" diameter="1.8796"/>
</package>
<package name="TACTILE_SWITCH_TALL">
<wire x1="-3" y1="-3" x2="3" y2="-3" width="0.254" layer="21"/>
<wire x1="3" y1="-3" x2="3" y2="3" width="0.254" layer="21"/>
<wire x1="3" y1="3" x2="-3" y2="3" width="0.254" layer="21"/>
<wire x1="-3" y1="3" x2="-3" y2="-3" width="0.254" layer="21"/>
<circle x="0" y="0" radius="1.75" width="0.254" layer="21"/>
<smd name="A1" x="-3.975" y="-2.25" dx="1.3" dy="1.55" layer="1" rot="R90"/>
<smd name="A2" x="3.975" y="-2.25" dx="1.3" dy="1.55" layer="1" rot="R90"/>
<smd name="B1" x="-3.975" y="2.25" dx="1.3" dy="1.55" layer="1" rot="R90"/>
<smd name="B2" x="3.975" y="2.25" dx="1.3" dy="1.55" layer="1" rot="R90"/>
</package>
<package name="REED_SWITCH_PLASTIC">
<wire x1="-7.5" y1="-1.65" x2="7.5" y2="-1.65" width="0.127" layer="21"/>
<wire x1="-7.5" y1="-1.65" x2="-7.5" y2="0" width="0.127" layer="21"/>
<wire x1="-7.5" y1="0" x2="-7.5" y2="1.65" width="0.127" layer="21"/>
<wire x1="-7.5" y1="1.65" x2="7.5" y2="1.65" width="0.127" layer="21"/>
<wire x1="7.5" y1="1.65" x2="7.5" y2="0" width="0.127" layer="21"/>
<wire x1="7.5" y1="0" x2="7.5" y2="-1.65" width="0.127" layer="21"/>
<wire x1="-7.5" y1="0" x2="-7.72" y2="0" width="0.127" layer="21"/>
<wire x1="7.5" y1="0" x2="7.72" y2="0" width="0.127" layer="21"/>
<pad name="P$1" x="-8.89" y="0" drill="1.016" diameter="1.8796"/>
<pad name="P$2" x="8.89" y="0" drill="1.016" diameter="1.8796"/>
</package>
<package name="TACTILE-PTH-SIDEEZ">
<wire x1="1.5" y1="-3.8" x2="-1.5" y2="-3.8" width="0.2032" layer="51"/>
<wire x1="-3.65" y1="-2" x2="-3.65" y2="3.5" width="0.2032" layer="51"/>
<wire x1="-3.65" y1="3.5" x2="-3" y2="3.5" width="0.2032" layer="51"/>
<wire x1="3" y1="3.5" x2="3.65" y2="3.5" width="0.2032" layer="51"/>
<wire x1="3.65" y1="3.5" x2="3.65" y2="-2" width="0.2032" layer="51"/>
<wire x1="-3" y1="2" x2="3" y2="2" width="0.2032" layer="51"/>
<wire x1="-3" y1="2" x2="-3" y2="3.5" width="0.2032" layer="51"/>
<wire x1="3" y1="2" x2="3" y2="3.5" width="0.2032" layer="51"/>
<wire x1="-3.65" y1="-2" x2="-1.5" y2="-2" width="0.2032" layer="51"/>
<wire x1="-1.5" y1="-2" x2="1.5" y2="-2" width="0.2032" layer="51"/>
<wire x1="1.5" y1="-2" x2="3.65" y2="-2" width="0.2032" layer="51"/>
<wire x1="1.5" y1="-2" x2="1.5" y2="-3.8" width="0.2032" layer="51"/>
<wire x1="-1.5" y1="-2" x2="-1.5" y2="-3.8" width="0.2032" layer="51"/>
<wire x1="-3.65" y1="1" x2="-3.65" y2="-2" width="0.2032" layer="21"/>
<wire x1="-3.65" y1="-2" x2="3.65" y2="-2" width="0.2032" layer="21"/>
<wire x1="3.65" y1="-2" x2="3.65" y2="1" width="0.2032" layer="21"/>
<wire x1="2" y1="2" x2="-2" y2="2" width="0.2032" layer="21"/>
<pad name="ANCHOR1" x="-3.5" y="2.5" drill="1.2" diameter="2.2" stop="no"/>
<pad name="ANCHOR2" x="3.5" y="2.5" drill="1.2" diameter="2.2" stop="no"/>
<pad name="1" x="-2.5" y="0" drill="0.8" diameter="1.7" stop="no"/>
<pad name="2" x="2.5" y="0" drill="0.8" diameter="1.7" stop="no"/>
<text x="-2.54" y="3.81" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<circle x="2.5" y="0" radius="0.4445" width="0" layer="29"/>
<circle x="-2.5" y="0" radius="0.4445" width="0" layer="29"/>
<circle x="-3.5" y="2.5" radius="0.635" width="0" layer="29"/>
<circle x="3.5" y="2.5" radius="0.635" width="0" layer="29"/>
<circle x="-3.5" y="2.5" radius="1.143" width="0" layer="30"/>
<circle x="2.5" y="0" radius="0.889" width="0" layer="30"/>
<circle x="-2.5" y="0" radius="0.889" width="0" layer="30"/>
<circle x="3.5" y="2.5" radius="1.143" width="0" layer="30"/>
</package>
<package name="TACTILE_SWITCH_SMD-3">
<wire x1="-2.04" y1="-0.44" x2="-2.04" y2="0.47" width="0.2032" layer="21"/>
<wire x1="-1.04" y1="1.14" x2="1.04" y2="1.14" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="0.8" width="0.15" layer="21"/>
<smd name="1" x="-1.8" y="1.1" dx="0.8" dy="1" layer="1" rot="R90"/>
<smd name="2" x="1.8" y="1.1" dx="0.8" dy="1" layer="1" rot="R90"/>
<smd name="3" x="-1.8" y="-1.1" dx="0.8" dy="1" layer="1" rot="R90"/>
<smd name="4" x="1.8" y="-1.1" dx="0.8" dy="1" layer="1" rot="R90"/>
<wire x1="2.06" y1="-0.44" x2="2.06" y2="0.47" width="0.2032" layer="21"/>
<wire x1="-1.04" y1="-1.16" x2="1.04" y2="-1.16" width="0.2032" layer="21"/>
</package>
<package name="TACTILE-SMD-12MM">
<wire x1="5" y1="-1.3" x2="5" y2="-0.7" width="0.2032" layer="51"/>
<wire x1="5" y1="-0.7" x2="4.5" y2="-0.2" width="0.2032" layer="51"/>
<wire x1="5" y1="0.2" x2="5" y2="1" width="0.2032" layer="51"/>
<wire x1="-6" y1="4" x2="-6" y2="5" width="0.2032" layer="21"/>
<wire x1="-5" y1="6" x2="5" y2="6" width="0.2032" layer="21"/>
<wire x1="6" y1="5" x2="6" y2="4" width="0.2032" layer="21"/>
<wire x1="6" y1="1" x2="6" y2="-1" width="0.2032" layer="21"/>
<wire x1="6" y1="-4" x2="6" y2="-5" width="0.2032" layer="21"/>
<wire x1="5" y1="-6" x2="-5" y2="-6" width="0.2032" layer="21"/>
<wire x1="-6" y1="-5" x2="-6" y2="-4" width="0.2032" layer="21"/>
<wire x1="-6" y1="-1" x2="-6" y2="1" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="3.5" width="0.2032" layer="21"/>
<circle x="-4.5" y="4.5" radius="0.3" width="0.7" layer="21"/>
<circle x="4.5" y="4.5" radius="0.3" width="0.7" layer="21"/>
<circle x="4.5" y="-4.5" radius="0.3" width="0.7" layer="21"/>
<circle x="-4.5" y="-4.5" radius="0.3" width="0.7" layer="21"/>
<smd name="4" x="-6.975" y="2.5" dx="1.6" dy="1.55" layer="1"/>
<smd name="2" x="-6.975" y="-2.5" dx="1.6" dy="1.55" layer="1"/>
<smd name="1" x="6.975" y="-2.5" dx="1.6" dy="1.55" layer="1"/>
<smd name="3" x="6.975" y="2.5" dx="1.6" dy="1.55" layer="1"/>
<wire x1="-6" y1="-5" x2="-5" y2="-6" width="0.2032" layer="21"/>
<wire x1="6" y1="-5" x2="5" y2="-6" width="0.2032" layer="21"/>
<wire x1="6" y1="5" x2="5" y2="6" width="0.2032" layer="21"/>
<wire x1="-5" y1="6" x2="-6" y2="5" width="0.2032" layer="21"/>
</package>
<package name="TACTILE-PTH-EZ">
<wire x1="3.048" y1="1.016" x2="3.048" y2="2.54" width="0.2032" layer="51"/>
<wire x1="3.048" y1="2.54" x2="2.54" y2="3.048" width="0.2032" layer="51"/>
<wire x1="2.54" y1="-3.048" x2="3.048" y2="-2.54" width="0.2032" layer="51"/>
<wire x1="3.048" y1="-2.54" x2="3.048" y2="-1.016" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="3.048" x2="-3.048" y2="2.54" width="0.2032" layer="51"/>
<wire x1="-3.048" y1="2.54" x2="-3.048" y2="1.016" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="-3.048" x2="-3.048" y2="-2.54" width="0.2032" layer="51"/>
<wire x1="-3.048" y1="-2.54" x2="-3.048" y2="-1.016" width="0.2032" layer="51"/>
<wire x1="2.54" y1="-3.048" x2="2.159" y2="-3.048" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="-3.048" x2="-2.159" y2="-3.048" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="3.048" x2="-2.159" y2="3.048" width="0.2032" layer="51"/>
<wire x1="2.54" y1="3.048" x2="2.159" y2="3.048" width="0.2032" layer="51"/>
<wire x1="2.159" y1="3.048" x2="-2.159" y2="3.048" width="0.2032" layer="21"/>
<wire x1="-2.159" y1="-3.048" x2="2.159" y2="-3.048" width="0.2032" layer="21"/>
<wire x1="3.048" y1="0.998" x2="3.048" y2="-1.016" width="0.2032" layer="21"/>
<wire x1="-3.048" y1="1.028" x2="-3.048" y2="-1.016" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="0.508" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="-0.508" x2="-2.54" y2="-1.27" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="0.508" x2="-2.159" y2="-0.381" width="0.2032" layer="51"/>
<circle x="0" y="0" radius="1.778" width="0.2032" layer="21"/>
<pad name="1" x="-3.2512" y="2.2606" drill="1.016" diameter="1.8796" stop="no"/>
<pad name="2" x="3.2512" y="2.2606" drill="1.016" diameter="1.8796" stop="no"/>
<pad name="3" x="-3.2512" y="-2.2606" drill="1.016" diameter="1.8796" stop="no"/>
<pad name="4" x="3.2512" y="-2.2606" drill="1.016" diameter="1.8796" stop="no"/>
<text x="-2.54" y="3.81" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<polygon width="0.127" layer="30">
<vertex x="-3.2664" y="3.142"/>
<vertex x="-3.2589" y="3.1445" curve="89.986886"/>
<vertex x="-4.1326" y="2.286"/>
<vertex x="-4.1351" y="2.2657" curve="90.00652"/>
<vertex x="-3.2563" y="1.392"/>
<vertex x="-3.2487" y="1.3869" curve="90.006616"/>
<vertex x="-2.3826" y="2.2403"/>
<vertex x="-2.3775" y="2.2683" curve="89.98711"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-3.2462" y="2.7026"/>
<vertex x="-3.2589" y="2.7051" curve="90.026544"/>
<vertex x="-3.6881" y="2.2733"/>
<vertex x="-3.6881" y="2.2632" curve="89.974074"/>
<vertex x="-3.2562" y="1.8213"/>
<vertex x="-3.2259" y="1.8186" curve="90.051271"/>
<vertex x="-2.8093" y="2.2658"/>
<vertex x="-2.8093" y="2.2606" curve="90.012964"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="3.2411" y="3.1395"/>
<vertex x="3.2486" y="3.142" curve="89.986886"/>
<vertex x="2.3749" y="2.2835"/>
<vertex x="2.3724" y="2.2632" curve="90.00652"/>
<vertex x="3.2512" y="1.3895"/>
<vertex x="3.2588" y="1.3844" curve="90.006616"/>
<vertex x="4.1249" y="2.2378"/>
<vertex x="4.13" y="2.2658" curve="89.98711"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="3.2613" y="2.7001"/>
<vertex x="3.2486" y="2.7026" curve="90.026544"/>
<vertex x="2.8194" y="2.2708"/>
<vertex x="2.8194" y="2.2607" curve="89.974074"/>
<vertex x="3.2513" y="1.8188"/>
<vertex x="3.2816" y="1.8161" curve="90.051271"/>
<vertex x="3.6982" y="2.2633"/>
<vertex x="3.6982" y="2.2581" curve="90.012964"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="-3.2613" y="-1.3868"/>
<vertex x="-3.2538" y="-1.3843" curve="89.986886"/>
<vertex x="-4.1275" y="-2.2428"/>
<vertex x="-4.13" y="-2.2631" curve="90.00652"/>
<vertex x="-3.2512" y="-3.1368"/>
<vertex x="-3.2436" y="-3.1419" curve="90.006616"/>
<vertex x="-2.3775" y="-2.2885"/>
<vertex x="-2.3724" y="-2.2605" curve="89.98711"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-3.2411" y="-1.8262"/>
<vertex x="-3.2538" y="-1.8237" curve="90.026544"/>
<vertex x="-3.683" y="-2.2555"/>
<vertex x="-3.683" y="-2.2656" curve="89.974074"/>
<vertex x="-3.2511" y="-2.7075"/>
<vertex x="-3.2208" y="-2.7102" curve="90.051271"/>
<vertex x="-2.8042" y="-2.263"/>
<vertex x="-2.8042" y="-2.2682" curve="90.012964"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="3.2411" y="-1.3843"/>
<vertex x="3.2486" y="-1.3818" curve="89.986886"/>
<vertex x="2.3749" y="-2.2403"/>
<vertex x="2.3724" y="-2.2606" curve="90.00652"/>
<vertex x="3.2512" y="-3.1343"/>
<vertex x="3.2588" y="-3.1394" curve="90.006616"/>
<vertex x="4.1249" y="-2.286"/>
<vertex x="4.13" y="-2.258" curve="89.98711"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="3.2613" y="-1.8237"/>
<vertex x="3.2486" y="-1.8212" curve="90.026544"/>
<vertex x="2.8194" y="-2.253"/>
<vertex x="2.8194" y="-2.2631" curve="89.974074"/>
<vertex x="3.2513" y="-2.705"/>
<vertex x="3.2816" y="-2.7077" curve="90.051271"/>
<vertex x="3.6982" y="-2.2605"/>
<vertex x="3.6982" y="-2.2657" curve="90.012964"/>
</polygon>
</package>
<package name="TACTILE-SWITCH-SMD">
<wire x1="-1.54" y1="-2.54" x2="-2.54" y2="-1.54" width="0.2032" layer="51"/>
<wire x1="-2.54" y1="-1.24" x2="-2.54" y2="1.27" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="1.54" x2="-1.54" y2="2.54" width="0.2032" layer="51"/>
<wire x1="-1.54" y1="2.54" x2="1.54" y2="2.54" width="0.2032" layer="21"/>
<wire x1="1.54" y1="2.54" x2="2.54" y2="1.54" width="0.2032" layer="51"/>
<wire x1="2.54" y1="1.24" x2="2.54" y2="-1.24" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-1.54" x2="1.54" y2="-2.54" width="0.2032" layer="51"/>
<wire x1="1.54" y1="-2.54" x2="-1.54" y2="-2.54" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="1.905" y2="0.445" width="0.127" layer="51"/>
<wire x1="1.905" y1="0.445" x2="2.16" y2="-0.01" width="0.127" layer="51"/>
<wire x1="1.905" y1="-0.23" x2="1.905" y2="-1.115" width="0.127" layer="51"/>
<circle x="0" y="0" radius="1.27" width="0.2032" layer="21"/>
<smd name="1" x="-2.794" y="1.905" dx="0.762" dy="1.524" layer="1" rot="R90"/>
<smd name="2" x="2.794" y="1.905" dx="0.762" dy="1.524" layer="1" rot="R90"/>
<smd name="3" x="-2.794" y="-1.905" dx="0.762" dy="1.524" layer="1" rot="R90"/>
<smd name="4" x="2.794" y="-1.905" dx="0.762" dy="1.524" layer="1" rot="R90"/>
<text x="-0.889" y="1.778" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.889" y="-2.032" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="TACTILE_SWITCH-SMD-RIGHT-ANGLE">
<hole x="0" y="0.9" drill="0.7"/>
<hole x="0" y="-0.9" drill="0.7"/>
<smd name="1" x="-1.95" y="0" dx="2" dy="1.1" layer="1" rot="R90"/>
<smd name="2" x="1.95" y="0" dx="2" dy="1.1" layer="1" rot="R90"/>
<wire x1="-2" y1="1.2" x2="-2" y2="1.5" width="0.127" layer="21"/>
<wire x1="-2" y1="1.5" x2="2" y2="1.5" width="0.127" layer="21"/>
<wire x1="2" y1="1.5" x2="2" y2="1.2" width="0.127" layer="21"/>
<wire x1="-2" y1="-1.2" x2="-2" y2="-1.5" width="0.127" layer="21"/>
<wire x1="-2" y1="-1.5" x2="-0.7" y2="-1.5" width="0.127" layer="21"/>
<wire x1="-0.7" y1="-1.5" x2="0.7" y2="-1.5" width="0.127" layer="21"/>
<wire x1="0.7" y1="-1.5" x2="2" y2="-1.5" width="0.127" layer="21"/>
<wire x1="2" y1="-1.5" x2="2" y2="-1.2" width="0.127" layer="21"/>
<wire x1="-0.7" y1="-2.1" x2="0.7" y2="-2.1" width="0.127" layer="21"/>
<wire x1="0.7" y1="-2.1" x2="0.7" y2="-1.5" width="0.127" layer="21"/>
<wire x1="-0.7" y1="-2.1" x2="-0.7" y2="-1.5" width="0.127" layer="21"/>
<text x="-2" y="1.7" size="0.8128" layer="25" ratio="15">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="SWITCH-MOMENTARY-2">
<wire x1="1.905" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="1.905" y2="1.27" width="0.254" layer="94"/>
<circle x="-2.54" y="0" radius="0.127" width="0.4064" layer="94"/>
<circle x="2.54" y="0" radius="0.127" width="0.4064" layer="94"/>
<text x="-2.54" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="2"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="SWITCH-MOMENTARY-2" prefix="S">
<description>Various NO switches- pushbuttons, reed, etc</description>
<gates>
<gate name="G$1" symbol="SWITCH-MOMENTARY-2" x="0" y="0"/>
</gates>
<devices>
<device name="PTH" package="TACTILE-PTH">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value=" SWCH-08441" constant="no"/>
</technology>
</technologies>
</device>
<device name="SMD-2" package="TACTILE_SWITCH_SMD-2">
<connects>
<connect gate="G$1" pin="1" pad="2"/>
<connect gate="G$1" pin="2" pad="1"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="SWCH-09213"/>
</technology>
</technologies>
</device>
<device name="12MM" package="TACTILE-PTH-12MM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="SWCH-09185" constant="no"/>
</technology>
</technologies>
</device>
<device name="SMD-1101NE" package="TACTILE-SWITCH-1101NE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="SWCH-00815" constant="no"/>
</technology>
</technologies>
</device>
<device name="PTH_REED" package="REED_SWITCH_PTH">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD-4" package="TACTILE_SWITCH_TALL">
<connects>
<connect gate="G$1" pin="1" pad="A2"/>
<connect gate="G$1" pin="2" pad="B2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="SWCH-11966" constant="no"/>
</technology>
</technologies>
</device>
<device name="PTH_REED2" package="REED_SWITCH_PLASTIC">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="SWCH-10467" constant="no"/>
</technology>
</technologies>
</device>
<device name="SIDE_EZ" package="TACTILE-PTH-SIDEEZ">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD-3" package="TACTILE_SWITCH_SMD-3">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD-12MM" package="TACTILE-SMD-12MM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH_EZ" package="TACTILE-PTH-EZ">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="TACTILE-SWITCH-SMD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="SWCH-08247" constant="no"/>
</technology>
</technologies>
</device>
<device name="SMD-REDUNDANT" package="TACTILE-SWITCH-SMD">
<connects>
<connect gate="G$1" pin="1" pad="1 2"/>
<connect gate="G$1" pin="2" pad="3 4"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="SWCH-08247" constant="no"/>
</technology>
</technologies>
</device>
<device name="TACTILE-SWITCH-SMD-RIGHT-ANGLE" package="TACTILE_SWITCH-SMD-RIGHT-ANGLE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="COMP-12265" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-FreqCtrl">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find crystals and oscillators and other things that go "tick".&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="HC49U-V">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-2.921" y1="-2.286" x2="2.921" y2="-2.286" width="0.4064" layer="21"/>
<wire x1="-2.921" y1="2.286" x2="2.921" y2="2.286" width="0.4064" layer="21"/>
<wire x1="-2.921" y1="-1.778" x2="2.921" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="2.921" y1="1.778" x2="-2.921" y2="1.778" width="0.1524" layer="21"/>
<wire x1="2.921" y1="1.778" x2="2.921" y2="-1.778" width="0.1524" layer="21" curve="-180"/>
<wire x1="2.921" y1="2.286" x2="2.921" y2="-2.286" width="0.4064" layer="21" curve="-180"/>
<wire x1="-2.921" y1="2.286" x2="-2.921" y2="-2.286" width="0.4064" layer="21" curve="180"/>
<wire x1="-2.921" y1="1.778" x2="-2.921" y2="-1.778" width="0.1524" layer="21" curve="180"/>
<wire x1="-0.254" y1="0.889" x2="0.254" y2="0.889" width="0.1524" layer="21"/>
<wire x1="0.254" y1="0.889" x2="0.254" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="0.254" y1="-0.889" x2="-0.254" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-0.889" x2="-0.254" y2="0.889" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0.889" x2="0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="0.635" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0.889" x2="-0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="1.27" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-1.27" y2="0" width="0.1524" layer="21"/>
<pad name="1" x="-2.413" y="0" drill="0.8128"/>
<pad name="2" x="2.413" y="0" drill="0.8128"/>
<text x="-5.08" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-4.191" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-3.81" y1="-2.794" x2="3.81" y2="2.794" layer="43"/>
<rectangle x1="-4.318" y1="-2.54" x2="-3.81" y2="2.54" layer="43"/>
<rectangle x1="-4.826" y1="-2.286" x2="-4.318" y2="2.286" layer="43"/>
<rectangle x1="-5.334" y1="-1.778" x2="-4.826" y2="1.778" layer="43"/>
<rectangle x1="-5.588" y1="-1.27" x2="-5.334" y2="1.016" layer="43"/>
<rectangle x1="3.81" y1="-2.54" x2="4.318" y2="2.54" layer="43"/>
<rectangle x1="4.318" y1="-2.286" x2="4.826" y2="2.286" layer="43"/>
<rectangle x1="4.826" y1="-1.778" x2="5.334" y2="1.778" layer="43"/>
<rectangle x1="5.334" y1="-1.016" x2="5.588" y2="1.016" layer="43"/>
</package>
<package name="TC38H">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-1.397" y1="1.651" x2="1.397" y2="1.651" width="0.1524" layer="21"/>
<wire x1="1.27" y1="9.906" x2="1.524" y2="9.652" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.524" y1="9.652" x2="-1.27" y2="9.906" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.27" y1="9.906" x2="1.27" y2="9.906" width="0.1524" layer="21"/>
<wire x1="1.397" y1="1.651" x2="1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="1.524" y1="2.032" x2="1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="1.524" y1="2.032" x2="1.524" y2="9.652" width="0.1524" layer="21"/>
<wire x1="-1.397" y1="1.651" x2="-1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="2.032" x2="-1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="2.032" x2="-1.524" y2="9.652" width="0.1524" layer="21"/>
<wire x1="1.397" y1="2.032" x2="-1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="0.5588" y1="0.7112" x2="0.508" y2="0.762" width="0.4064" layer="21"/>
<wire x1="0.508" y1="0.762" x2="0.508" y2="1.143" width="0.4064" layer="21"/>
<wire x1="-0.508" y1="0.762" x2="-0.508" y2="1.016" width="0.4064" layer="21"/>
<wire x1="-0.5588" y1="0.7112" x2="-0.508" y2="0.762" width="0.4064" layer="21"/>
<wire x1="0.635" y1="0.635" x2="1.27" y2="0" width="0.1524" layer="51"/>
<wire x1="-0.635" y1="0.635" x2="-1.27" y2="0" width="0.1524" layer="51"/>
<wire x1="-0.762" y1="5.588" x2="-0.762" y2="5.207" width="0.1524" layer="21"/>
<wire x1="0.762" y1="5.207" x2="-0.762" y2="5.207" width="0.1524" layer="21"/>
<wire x1="0.762" y1="5.207" x2="0.762" y2="5.588" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="5.588" x2="0.762" y2="5.588" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="5.969" x2="0" y2="5.969" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="4.826" x2="0" y2="4.826" width="0.1524" layer="21"/>
<wire x1="0" y1="4.826" x2="0" y2="4.318" width="0.1524" layer="21"/>
<wire x1="0" y1="4.826" x2="0.762" y2="4.826" width="0.1524" layer="21"/>
<wire x1="0" y1="5.969" x2="0" y2="6.477" width="0.1524" layer="21"/>
<wire x1="0" y1="5.969" x2="0.762" y2="5.969" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="0.8128" diameter="1.6764"/>
<pad name="2" x="1.27" y="0" drill="0.8128" diameter="1.6764"/>
<text x="-1.905" y="2.032" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.175" y="2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="0.3048" y1="1.016" x2="0.7112" y2="1.6002" layer="21"/>
<rectangle x1="-0.7112" y1="1.016" x2="-0.3048" y2="1.6002" layer="21"/>
<rectangle x1="-1.778" y1="1.016" x2="1.778" y2="10.414" layer="43"/>
</package>
<package name="TC26H">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-0.889" y1="1.651" x2="0.889" y2="1.651" width="0.1524" layer="21"/>
<wire x1="0.762" y1="7.747" x2="1.016" y2="7.493" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.016" y1="7.493" x2="-0.762" y2="7.747" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.762" y1="7.747" x2="0.762" y2="7.747" width="0.1524" layer="21"/>
<wire x1="0.889" y1="1.651" x2="0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="1.016" y1="2.032" x2="1.016" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-0.889" y1="1.651" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="2.032" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="2.032" x2="-1.016" y2="7.493" width="0.1524" layer="21"/>
<wire x1="0.508" y1="0.762" x2="0.508" y2="1.143" width="0.4064" layer="21"/>
<wire x1="-0.508" y1="0.762" x2="-0.508" y2="1.27" width="0.4064" layer="21"/>
<wire x1="0.635" y1="0.635" x2="1.27" y2="0" width="0.4064" layer="51"/>
<wire x1="-0.635" y1="0.635" x2="-1.27" y2="0" width="0.4064" layer="51"/>
<wire x1="-0.508" y1="4.953" x2="-0.508" y2="4.572" width="0.1524" layer="21"/>
<wire x1="0.508" y1="4.572" x2="-0.508" y2="4.572" width="0.1524" layer="21"/>
<wire x1="0.508" y1="4.572" x2="0.508" y2="4.953" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="4.953" x2="0.508" y2="4.953" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="5.334" x2="0" y2="5.334" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="4.191" x2="0" y2="4.191" width="0.1524" layer="21"/>
<wire x1="0" y1="4.191" x2="0" y2="3.683" width="0.1524" layer="21"/>
<wire x1="0" y1="4.191" x2="0.508" y2="4.191" width="0.1524" layer="21"/>
<wire x1="0" y1="5.334" x2="0" y2="5.842" width="0.1524" layer="21"/>
<wire x1="0" y1="5.334" x2="0.508" y2="5.334" width="0.1524" layer="21"/>
<wire x1="1.016" y1="2.032" x2="0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="0.889" y1="2.032" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="0.8128" diameter="1.6764"/>
<pad name="2" x="1.27" y="0" drill="0.8128" diameter="1.6764"/>
<text x="-1.397" y="2.032" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="2.667" y="2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="0.3048" y1="1.016" x2="0.7112" y2="1.6002" layer="21"/>
<rectangle x1="-0.7112" y1="1.016" x2="-0.3048" y2="1.6002" layer="21"/>
<rectangle x1="-1.778" y1="0.762" x2="1.778" y2="8.382" layer="43"/>
</package>
<package name="HC49UP">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-5.1091" y1="1.143" x2="-3.429" y2="2.0321" width="0.0508" layer="21" curve="-55.770993" cap="flat"/>
<wire x1="-5.715" y1="1.143" x2="-5.715" y2="2.159" width="0.1524" layer="21"/>
<wire x1="3.429" y1="2.032" x2="5.1091" y2="1.143" width="0.0508" layer="21" curve="-55.772485" cap="flat"/>
<wire x1="5.715" y1="1.143" x2="5.715" y2="2.159" width="0.1524" layer="21"/>
<wire x1="3.429" y1="-1.27" x2="-3.429" y2="-1.27" width="0.0508" layer="21"/>
<wire x1="3.429" y1="-2.032" x2="-3.429" y2="-2.032" width="0.0508" layer="21"/>
<wire x1="-3.429" y1="1.27" x2="3.429" y2="1.27" width="0.0508" layer="21"/>
<wire x1="5.461" y1="-2.413" x2="-5.461" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-0.381" x2="6.477" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="5.715" y1="0.381" x2="6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="6.477" y1="-0.381" x2="6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="5.461" y1="-2.413" x2="5.715" y2="-2.159" width="0.1524" layer="21" curve="90"/>
<wire x1="5.715" y1="-1.143" x2="5.715" y2="1.143" width="0.1524" layer="51"/>
<wire x1="5.715" y1="-2.159" x2="5.715" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="3.429" y1="-1.27" x2="3.9826" y2="-1.143" width="0.0508" layer="21" curve="25.842828" cap="flat"/>
<wire x1="3.429" y1="1.27" x2="3.9826" y2="1.143" width="0.0508" layer="21" curve="-25.842828" cap="flat"/>
<wire x1="3.429" y1="-2.032" x2="5.109" y2="-1.1429" width="0.0508" layer="21" curve="55.771157" cap="flat"/>
<wire x1="3.9826" y1="-1.143" x2="3.9826" y2="1.143" width="0.0508" layer="51" curve="128.314524" cap="flat"/>
<wire x1="5.1091" y1="-1.143" x2="5.1091" y2="1.143" width="0.0508" layer="51" curve="68.456213" cap="flat"/>
<wire x1="-5.1091" y1="-1.143" x2="-3.429" y2="-2.032" width="0.0508" layer="21" curve="55.772485" cap="flat"/>
<wire x1="-3.9826" y1="-1.143" x2="-3.9826" y2="1.143" width="0.0508" layer="51" curve="-128.314524" cap="flat"/>
<wire x1="-3.9826" y1="-1.143" x2="-3.429" y2="-1.27" width="0.0508" layer="21" curve="25.842828" cap="flat"/>
<wire x1="-3.9826" y1="1.143" x2="-3.429" y2="1.27" width="0.0508" layer="21" curve="-25.842828" cap="flat"/>
<wire x1="-6.477" y1="-0.381" x2="-6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-5.1091" y1="-1.143" x2="-5.1091" y2="1.143" width="0.0508" layer="51" curve="-68.456213" cap="flat"/>
<wire x1="-5.715" y1="-1.143" x2="-5.715" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="-0.381" x2="-5.715" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="0.381" x2="-5.715" y2="1.143" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="-2.159" x2="-5.715" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.159" x2="-5.461" y2="-2.413" width="0.1524" layer="21" curve="90"/>
<wire x1="-5.715" y1="-0.381" x2="-6.477" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="0.381" x2="-6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-3.429" y1="2.032" x2="3.429" y2="2.032" width="0.0508" layer="21"/>
<wire x1="5.461" y1="2.413" x2="-5.461" y2="2.413" width="0.1524" layer="21"/>
<wire x1="5.461" y1="2.413" x2="5.715" y2="2.159" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.715" y1="2.159" x2="-5.461" y2="2.413" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.254" y1="0.635" x2="-0.254" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-0.635" x2="0.254" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.254" y1="-0.635" x2="0.254" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0.254" y1="0.635" x2="-0.254" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0.635" x2="-0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-1.016" y2="0" width="0.0508" layer="21"/>
<wire x1="0.635" y1="0.635" x2="0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="0.635" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="1.016" y2="0" width="0.0508" layer="21"/>
<smd name="1" x="-4.826" y="0" dx="5.334" dy="1.9304" layer="1"/>
<smd name="2" x="4.826" y="0" dx="5.334" dy="1.9304" layer="1"/>
<text x="-5.715" y="2.794" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.715" y="-4.191" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-6.604" y1="-3.048" x2="6.604" y2="3.048" layer="43"/>
</package>
<package name="HC49US">
<description>&lt;B&gt;CRYSTAL&lt;/B&gt;</description>
<wire x1="-3.429" y1="-2.286" x2="3.429" y2="-2.286" width="0.2032" layer="21"/>
<wire x1="3.429" y1="2.286" x2="-3.429" y2="2.286" width="0.2032" layer="21"/>
<wire x1="3.429" y1="2.286" x2="3.429" y2="-2.286" width="0.2032" layer="21" curve="-180"/>
<wire x1="-3.429" y1="2.286" x2="-3.429" y2="-2.286" width="0.2032" layer="21" curve="180"/>
<pad name="1" x="-2.54" y="0" drill="0.7" diameter="1.651" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="0.7" diameter="1.651" rot="R90"/>
<text x="-5.08" y="-3.937" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-5.08" y="2.667" size="1.27" layer="25" ratio="10">&gt;NAME</text>
</package>
<package name="CRYSTAL-32KHZ-SMD">
<smd name="X1" x="-1.27" y="0" dx="1" dy="2.5" layer="1"/>
<smd name="X2" x="1.27" y="0" dx="1" dy="2.5" layer="1"/>
<smd name="SHEILD" x="0" y="5.08" dx="2.5" dy="6" layer="1"/>
<text x="-0.635" y="8.255" size="0.4064" layer="25">&gt;Name</text>
<text x="-0.635" y="-1.905" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="CRYSTAL-SMD-5X3">
<wire x1="-0.6" y1="1.6" x2="0.6" y2="1.6" width="0.2032" layer="21"/>
<wire x1="2.5" y1="0.3" x2="2.5" y2="-0.3" width="0.2032" layer="21"/>
<wire x1="0.6" y1="-1.6" x2="-0.6" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="0.3" x2="-2.5" y2="-0.3" width="0.2032" layer="21"/>
<smd name="1" x="-1.85" y="-1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="3" x="1.85" y="1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="4" x="-1.85" y="1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="2" x="1.85" y="-1.15" dx="1.9" dy="1.1" layer="1"/>
<text x="-2.54" y="1.905" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.54" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="CRYSTAL-32KHZ-SMD_EPSON_MC146">
<wire x1="0.2" y1="0" x2="7.2" y2="0" width="0.127" layer="51"/>
<wire x1="7.2" y1="0" x2="7.2" y2="1.5" width="0.127" layer="51"/>
<wire x1="7.2" y1="1.5" x2="0.2" y2="1.5" width="0.127" layer="51"/>
<wire x1="0.2" y1="1.5" x2="0.2" y2="0" width="0.127" layer="51"/>
<wire x1="6.2" y1="1.4" x2="5.9" y2="1.4" width="0.127" layer="21"/>
<wire x1="5.9" y1="1.4" x2="5.9" y2="0.1" width="0.127" layer="21"/>
<wire x1="5.9" y1="0.1" x2="6.2" y2="0.1" width="0.127" layer="21"/>
<wire x1="1.3" y1="1.4" x2="1.9" y2="1.4" width="0.127" layer="21"/>
<wire x1="1.3" y1="0.1" x2="1.9" y2="0.1" width="0.127" layer="21"/>
<smd name="P$1" x="0.6" y="0.3" dx="1.2" dy="0.6" layer="1"/>
<smd name="P$2" x="0.6" y="1.2" dx="1.2" dy="0.6" layer="1"/>
<smd name="NC2" x="6.9" y="0.3" dx="1.2" dy="0.6" layer="1"/>
<smd name="NC1" x="6.9" y="1.2" dx="1.2" dy="0.6" layer="1"/>
</package>
<package name="CRYSTAL-SMD-10.5X4.8-2PIN">
<wire x1="-6.2" y1="1.5" x2="-6.2" y2="2.4" width="0.127" layer="21"/>
<wire x1="-6.2" y1="2.4" x2="6.2" y2="2.4" width="0.127" layer="21"/>
<wire x1="6.2" y1="2.4" x2="6.2" y2="1.5" width="0.127" layer="21"/>
<wire x1="-6.2" y1="-1.5" x2="-6.2" y2="-2.4" width="0.127" layer="21"/>
<wire x1="-6.2" y1="-2.4" x2="6.2" y2="-2.4" width="0.127" layer="21"/>
<wire x1="6.2" y1="-2.4" x2="6.2" y2="-1.5" width="0.127" layer="21"/>
<smd name="P$1" x="-4.3" y="0" dx="5.5" dy="1.5" layer="1"/>
<smd name="P$2" x="4.3" y="0" dx="5.5" dy="1.5" layer="1"/>
</package>
<package name="TC26HEZ">
<description>32kHz crystal package&lt;br&gt;
This is the "EZ" version, which has limited top masking for improved ease of assembly.</description>
<wire x1="-0.889" y1="1.651" x2="0.889" y2="1.651" width="0.1524" layer="21"/>
<wire x1="0.762" y1="7.747" x2="1.016" y2="7.493" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.016" y1="7.493" x2="-0.762" y2="7.747" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.762" y1="7.747" x2="0.762" y2="7.747" width="0.1524" layer="21"/>
<wire x1="0.889" y1="1.651" x2="0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="1.016" y1="2.032" x2="1.016" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-0.889" y1="1.651" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="2.032" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="2.032" x2="-1.016" y2="7.493" width="0.1524" layer="21"/>
<wire x1="0.508" y1="0.762" x2="0.508" y2="1.143" width="0.4064" layer="21"/>
<wire x1="-0.508" y1="0.762" x2="-0.508" y2="1.27" width="0.4064" layer="21"/>
<wire x1="0.635" y1="0.635" x2="1.27" y2="0" width="0.4064" layer="51"/>
<wire x1="-0.635" y1="0.635" x2="-1.27" y2="0" width="0.4064" layer="51"/>
<wire x1="-0.508" y1="4.953" x2="-0.508" y2="4.572" width="0.1524" layer="21"/>
<wire x1="0.508" y1="4.572" x2="-0.508" y2="4.572" width="0.1524" layer="21"/>
<wire x1="0.508" y1="4.572" x2="0.508" y2="4.953" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="4.953" x2="0.508" y2="4.953" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="5.334" x2="0" y2="5.334" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="4.191" x2="0" y2="4.191" width="0.1524" layer="21"/>
<wire x1="0" y1="4.191" x2="0" y2="3.683" width="0.1524" layer="21"/>
<wire x1="0" y1="4.191" x2="0.508" y2="4.191" width="0.1524" layer="21"/>
<wire x1="0" y1="5.334" x2="0" y2="5.842" width="0.1524" layer="21"/>
<wire x1="0" y1="5.334" x2="0.508" y2="5.334" width="0.1524" layer="21"/>
<wire x1="1.016" y1="2.032" x2="0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="0.889" y1="2.032" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="0.8128" diameter="1.6764" stop="no"/>
<pad name="2" x="1.27" y="0" drill="0.8128" diameter="1.6764" stop="no"/>
<text x="-1.397" y="2.032" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="2.667" y="2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="0.3048" y1="1.016" x2="0.7112" y2="1.6002" layer="21"/>
<rectangle x1="-0.7112" y1="1.016" x2="-0.3048" y2="1.6002" layer="21"/>
<rectangle x1="-1.778" y1="0.762" x2="1.778" y2="8.382" layer="43"/>
<circle x="-1.27" y="0" radius="0.508" width="0" layer="29"/>
<circle x="1.27" y="0" radius="0.508" width="0" layer="29"/>
<circle x="-1.27" y="0" radius="0.924571875" width="0" layer="30"/>
<circle x="1.27" y="0" radius="0.915809375" width="0" layer="30"/>
</package>
<package name="CRYSTAL-TXC-7A">
<smd name="P$1" x="1.85" y="0" dx="1.7" dy="2.4" layer="1"/>
<smd name="P$2" x="-1.85" y="0" dx="1.7" dy="2.4" layer="1"/>
<wire x1="-2.6" y1="1.6" x2="2.6" y2="1.6" width="0.127" layer="21"/>
<wire x1="2.6" y1="-1.6" x2="-2.6" y2="-1.6" width="0.127" layer="21"/>
<text x="-1.016" y="0.254" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-0.508" size="0.4064" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="Q">
<wire x1="1.016" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.016" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="1.524" x2="-0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-0.381" y1="-1.524" x2="0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="-1.524" x2="0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="1.524" x2="-0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="1.016" y1="1.778" x2="1.016" y2="-1.778" width="0.254" layer="94"/>
<wire x1="-1.016" y1="1.778" x2="-1.016" y2="-1.778" width="0.254" layer="94"/>
<text x="2.54" y="1.016" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.159" y="-1.143" size="0.8636" layer="93">1</text>
<text x="1.524" y="-1.143" size="0.8636" layer="93">2</text>
<pin name="2" x="2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CRYSTAL" prefix="Y" uservalue="yes">
<description>Various standard crystals. Proven footprints.</description>
<gates>
<gate name="G$1" symbol="Q" x="0" y="0"/>
</gates>
<devices>
<device name="HC49UV" package="HC49U-V">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="TC38H" package="TC38H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="TC26H" package="TC26H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="XTAL-10112"/>
<attribute name="VALUE" value="32.768kHz"/>
</technology>
</technologies>
</device>
<device name="SMD" package="HC49UP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="HC49US" package="HC49US">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="32-SMD" package="CRYSTAL-32KHZ-SMD">
<connects>
<connect gate="G$1" pin="1" pad="X1"/>
<connect gate="G$1" pin="2" pad="X2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="XTAL-07894" constant="no"/>
</technology>
</technologies>
</device>
<device name="5X3" package="CRYSTAL-SMD-5X3">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="XTAL-08218" constant="no"/>
</technology>
</technologies>
</device>
<device name="EPSONMC146" package="CRYSTAL-32KHZ-SMD_EPSON_MC146">
<connects>
<connect gate="G$1" pin="1" pad="P$2"/>
<connect gate="G$1" pin="2" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="10.5X4.8" package="CRYSTAL-SMD-10.5X4.8-2PIN">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="TC26H_EZ" package="TC26HEZ">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="TXC-7A" package="CRYSTAL-TXC-7A">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-LED">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find discrete LEDs for illumination or indication, but no displays.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="LED5MM">
<description>&lt;B&gt;LED&lt;/B&gt;&lt;p&gt;
5 mm, round</description>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="1.905" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="1.905" width="0.254" layer="21" curve="-286.260205" cap="flat"/>
<wire x1="-1.143" y1="0" x2="0" y2="1.143" width="0.1524" layer="51" curve="-90" cap="flat"/>
<wire x1="0" y1="-1.143" x2="1.143" y2="0" width="0.1524" layer="51" curve="90" cap="flat"/>
<wire x1="-1.651" y1="0" x2="0" y2="1.651" width="0.1524" layer="51" curve="-90" cap="flat"/>
<wire x1="0" y1="-1.651" x2="1.651" y2="0" width="0.1524" layer="51" curve="90" cap="flat"/>
<wire x1="-2.159" y1="0" x2="0" y2="2.159" width="0.1524" layer="51" curve="-90" cap="flat"/>
<wire x1="0" y1="-2.159" x2="2.159" y2="0" width="0.1524" layer="51" curve="90" cap="flat"/>
<circle x="0" y="0" radius="2.54" width="0.1524" layer="21"/>
<pad name="A" x="-1.27" y="0" drill="0.8128" diameter="1.8796"/>
<pad name="K" x="1.27" y="0" drill="0.8128" diameter="1.8796"/>
<text x="3.175" y="0.5334" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="3.2004" y="-1.8034" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="LED3MM">
<description>&lt;B&gt;LED&lt;/B&gt;&lt;p&gt;
3 mm, round</description>
<wire x1="1.5748" y1="-1.27" x2="1.5748" y2="1.27" width="0.254" layer="51"/>
<wire x1="0" y1="2.032" x2="1.561" y2="1.3009" width="0.254" layer="21" curve="-50.193108" cap="flat"/>
<wire x1="-1.7929" y1="0.9562" x2="0" y2="2.032" width="0.254" layer="21" curve="-61.926949" cap="flat"/>
<wire x1="0" y1="-2.032" x2="1.5512" y2="-1.3126" width="0.254" layer="21" curve="49.763022" cap="flat"/>
<wire x1="-1.7643" y1="-1.0082" x2="0" y2="-2.032" width="0.254" layer="21" curve="60.255215" cap="flat"/>
<wire x1="-2.032" y1="0" x2="-1.7891" y2="0.9634" width="0.254" layer="51" curve="-28.301701" cap="flat"/>
<wire x1="-2.032" y1="0" x2="-1.7306" y2="-1.065" width="0.254" layer="51" curve="31.60822" cap="flat"/>
<wire x1="1.5748" y1="1.2954" x2="1.5748" y2="0.7874" width="0.254" layer="21"/>
<wire x1="1.5748" y1="-1.2954" x2="1.5748" y2="-0.8382" width="0.254" layer="21"/>
<pad name="A" x="-1.27" y="0" drill="0.8128" diameter="1.8796"/>
<pad name="K" x="1.27" y="0" drill="0.8128" diameter="1.8796"/>
<text x="1.905" y="0.381" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="1.905" y="-1.651" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="LED-1206">
<wire x1="-1" y1="1" x2="-2.4" y2="1" width="0.2032" layer="21"/>
<wire x1="-2.4" y1="1" x2="-2.4" y2="-1" width="0.2032" layer="21"/>
<wire x1="-2.4" y1="-1" x2="-1" y2="-1" width="0.2032" layer="21"/>
<wire x1="1" y1="1" x2="2.4" y2="1" width="0.2032" layer="21"/>
<wire x1="2.4" y1="1" x2="2.4" y2="-1" width="0.2032" layer="21"/>
<wire x1="2.4" y1="-1" x2="1" y2="-1" width="0.2032" layer="21"/>
<wire x1="0.3" y1="0.7" x2="0.3" y2="0" width="0.2032" layer="21"/>
<wire x1="0.3" y1="0" x2="0.3" y2="-0.7" width="0.2032" layer="21"/>
<wire x1="0.3" y1="0" x2="-0.3" y2="0.6" width="0.2032" layer="21"/>
<wire x1="-0.3" y1="0.6" x2="-0.3" y2="-0.6" width="0.2032" layer="21"/>
<wire x1="-0.3" y1="-0.6" x2="0.3" y2="0" width="0.2032" layer="21"/>
<smd name="A" x="-1.5" y="0" dx="1.2" dy="1.4" layer="1"/>
<smd name="C" x="1.5" y="0" dx="1.2" dy="1.4" layer="1"/>
<text x="-0.889" y="1.397" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.778" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="LED-0603">
<wire x1="0.46" y1="0.17" x2="0" y2="0.17" width="0.2032" layer="21"/>
<wire x1="-0.46" y1="0.17" x2="0" y2="0.17" width="0.2032" layer="21"/>
<wire x1="0" y1="0.17" x2="0.2338" y2="-0.14" width="0.2032" layer="21"/>
<wire x1="-0.0254" y1="0.1546" x2="-0.2184" y2="-0.14" width="0.2032" layer="21"/>
<smd name="C" x="0" y="0.877" dx="1" dy="1" layer="1" roundness="30"/>
<smd name="A" x="0" y="-0.877" dx="1" dy="1" layer="1" roundness="30"/>
<text x="-0.6985" y="-0.889" size="0.4064" layer="25" rot="R90">&gt;NAME</text>
<text x="1.0795" y="-1.016" size="0.4064" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="LED10MM">
<wire x1="-5" y1="-2" x2="-5" y2="2" width="0.2032" layer="21" curve="316.862624"/>
<wire x1="-5" y1="2" x2="-5" y2="-2" width="0.2032" layer="21"/>
<pad name="A" x="2.54" y="0" drill="2.4" diameter="3.7"/>
<pad name="C" x="-2.54" y="0" drill="2.4" diameter="3.7" shape="square"/>
<text x="2.159" y="2.54" size="1.016" layer="51" ratio="15">L</text>
<text x="-2.921" y="2.54" size="1.016" layer="51" ratio="15">S</text>
</package>
<package name="FKIT-LED-1206">
<wire x1="1.55" y1="-0.75" x2="-1.55" y2="-0.75" width="0.1016" layer="51"/>
<wire x1="-1.55" y1="-0.75" x2="-1.55" y2="0.75" width="0.1016" layer="51"/>
<wire x1="-1.55" y1="0.75" x2="1.55" y2="0.75" width="0.1016" layer="51"/>
<wire x1="1.55" y1="0.75" x2="1.55" y2="-0.75" width="0.1016" layer="51"/>
<wire x1="-0.55" y1="-0.5" x2="0.55" y2="-0.5" width="0.1016" layer="21" curve="95.452622"/>
<wire x1="-0.55" y1="0.5" x2="-0.55" y2="-0.5" width="0.1016" layer="51" curve="84.547378"/>
<wire x1="0.55" y1="0.5" x2="-0.55" y2="0.5" width="0.1016" layer="21" curve="95.452622"/>
<wire x1="0.55" y1="-0.5" x2="0.55" y2="0.5" width="0.1016" layer="51" curve="84.547378"/>
<smd name="A" x="-1.422" y="0" dx="1.6" dy="1.803" layer="1"/>
<smd name="C" x="1.422" y="0" dx="1.6" dy="1.803" layer="1"/>
<text x="-1.27" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.1" y1="-0.1" x2="0.1" y2="0.1" layer="21"/>
<rectangle x1="0.45" y1="-0.7" x2="0.8" y2="-0.45" layer="51"/>
<rectangle x1="0.8" y1="-0.7" x2="0.9" y2="0.5" layer="51"/>
<rectangle x1="0.8" y1="0.55" x2="0.9" y2="0.7" layer="51"/>
<rectangle x1="-0.9" y1="-0.7" x2="-0.8" y2="0.5" layer="51"/>
<rectangle x1="-0.9" y1="0.55" x2="-0.8" y2="0.7" layer="51"/>
<rectangle x1="0.45" y1="-0.7" x2="0.6" y2="-0.45" layer="21"/>
</package>
<package name="LED3MM-NS">
<description>&lt;h3&gt;LED 3MM - No Silk&lt;/h3&gt;
3 mm, round</description>
<wire x1="1.5748" y1="-1.27" x2="1.5748" y2="1.27" width="0.254" layer="51"/>
<wire x1="0" y1="2.032" x2="1.561" y2="1.3009" width="0.254" layer="51" curve="-50.193108" cap="flat"/>
<wire x1="-1.7929" y1="0.9562" x2="0" y2="2.032" width="0.254" layer="51" curve="-61.926949" cap="flat"/>
<wire x1="0" y1="-2.032" x2="1.5512" y2="-1.3126" width="0.254" layer="51" curve="49.763022" cap="flat"/>
<wire x1="-1.7643" y1="-1.0082" x2="0" y2="-2.032" width="0.254" layer="51" curve="60.255215" cap="flat"/>
<wire x1="-2.032" y1="0" x2="-1.7891" y2="0.9634" width="0.254" layer="51" curve="-28.301701" cap="flat"/>
<wire x1="-2.032" y1="0" x2="-1.7306" y2="-1.065" width="0.254" layer="51" curve="31.60822" cap="flat"/>
<wire x1="1.5748" y1="1.2954" x2="1.5748" y2="0.7874" width="0.254" layer="51"/>
<wire x1="1.5748" y1="-1.2954" x2="1.5748" y2="-0.8382" width="0.254" layer="51"/>
<pad name="A" x="-1.27" y="0" drill="0.8128"/>
<pad name="K" x="1.27" y="0" drill="0.8128"/>
<text x="1.905" y="0.381" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="1.905" y="-1.651" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="LED5MM-KIT">
<description>&lt;h3&gt;LED5MM-KIT&lt;/h3&gt;
5MM Through-hole LED&lt;br&gt;
&lt;br&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has a smaller diameter top stop mask, which doesn't cover the diameter of the pad. This means only the bottom side of the pads' copper will be exposed. You'll only be able to solder to the bottom side.</description>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="1.905" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="1.905" width="0.254" layer="21" curve="-286.260205" cap="flat"/>
<wire x1="-1.143" y1="0" x2="0" y2="1.143" width="0.1524" layer="51" curve="-90" cap="flat"/>
<wire x1="0" y1="-1.143" x2="1.143" y2="0" width="0.1524" layer="51" curve="90" cap="flat"/>
<wire x1="-1.651" y1="0" x2="0" y2="1.651" width="0.1524" layer="51" curve="-90" cap="flat"/>
<wire x1="0" y1="-1.651" x2="1.651" y2="0" width="0.1524" layer="51" curve="90" cap="flat"/>
<wire x1="-2.159" y1="0" x2="0" y2="2.159" width="0.1524" layer="51" curve="-90" cap="flat"/>
<wire x1="0" y1="-2.159" x2="2.159" y2="0" width="0.1524" layer="51" curve="90" cap="flat"/>
<circle x="0" y="0" radius="2.54" width="0.1524" layer="21"/>
<pad name="A" x="-1.27" y="0" drill="0.8128" diameter="1.8796" stop="no"/>
<pad name="K" x="1.27" y="0" drill="0.8128" diameter="1.8796" stop="no"/>
<text x="3.175" y="0.5334" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="3.2004" y="-1.8034" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<polygon width="0.127" layer="30">
<vertex x="-1.2675" y="-0.9525" curve="-90"/>
<vertex x="-2.2224" y="-0.0228" curve="-90.011749"/>
<vertex x="-1.27" y="0.9526" curve="-90"/>
<vertex x="-0.32" y="-0.0254" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-1.27" y="-0.4445" curve="-90.012891"/>
<vertex x="-1.7145" y="-0.0203" curve="-90"/>
<vertex x="-1.27" y="0.447" curve="-90"/>
<vertex x="-0.8281" y="-0.0101" curve="-90.012967"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="1.2725" y="-0.9525" curve="-90"/>
<vertex x="0.3176" y="-0.0228" curve="-90.011749"/>
<vertex x="1.27" y="0.9526" curve="-90"/>
<vertex x="2.22" y="-0.0254" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="1.27" y="-0.4445" curve="-90.012891"/>
<vertex x="0.8255" y="-0.0203" curve="-90"/>
<vertex x="1.27" y="0.447" curve="-90"/>
<vertex x="1.7119" y="-0.0101" curve="-90.012967"/>
</polygon>
</package>
<package name="LED-1206-BOTTOM">
<wire x1="-2" y1="0.4" x2="-2" y2="-0.4" width="0.127" layer="49"/>
<wire x1="-2.4" y1="0" x2="-1.6" y2="0" width="0.127" layer="49"/>
<wire x1="1.6" y1="0" x2="2.4" y2="0" width="0.127" layer="49"/>
<wire x1="-1.27" y1="0" x2="-0.381" y2="0" width="0.127" layer="49"/>
<wire x1="-0.381" y1="0" x2="-0.381" y2="0.635" width="0.127" layer="49"/>
<wire x1="-0.381" y1="0.635" x2="0.254" y2="0" width="0.127" layer="49"/>
<wire x1="0.254" y1="0" x2="-0.381" y2="-0.635" width="0.127" layer="49"/>
<wire x1="-0.381" y1="-0.635" x2="-0.381" y2="0" width="0.127" layer="49"/>
<wire x1="0.254" y1="0" x2="0.254" y2="0.635" width="0.127" layer="49"/>
<wire x1="0.254" y1="0" x2="0.254" y2="-0.635" width="0.127" layer="49"/>
<wire x1="0.254" y1="0" x2="1.27" y2="0" width="0.127" layer="49"/>
<rectangle x1="-0.75" y1="-0.75" x2="0.75" y2="0.75" layer="51"/>
<smd name="A" x="-1.8" y="0" dx="1.5" dy="1.6" layer="1"/>
<smd name="C" x="1.8" y="0" dx="1.5" dy="1.6" layer="1"/>
<hole x="0" y="0" drill="2.3"/>
<polygon width="0" layer="51">
<vertex x="1.1" y="-0.5"/>
<vertex x="1.1" y="0.5"/>
<vertex x="1.6" y="0.5"/>
<vertex x="1.6" y="0.25" curve="90"/>
<vertex x="1.4" y="0.05"/>
<vertex x="1.4" y="-0.05" curve="90"/>
<vertex x="1.6" y="-0.25"/>
<vertex x="1.6" y="-0.5"/>
</polygon>
<polygon width="0" layer="51">
<vertex x="-1.1" y="0.5"/>
<vertex x="-1.1" y="-0.5"/>
<vertex x="-1.6" y="-0.5"/>
<vertex x="-1.6" y="-0.25" curve="90"/>
<vertex x="-1.4" y="-0.05"/>
<vertex x="-1.4" y="0.05" curve="90"/>
<vertex x="-1.6" y="0.25"/>
<vertex x="-1.6" y="0.5"/>
</polygon>
<wire x1="1.016" y1="1.016" x2="2.7686" y2="1.016" width="0.127" layer="21"/>
<wire x1="2.7686" y1="1.016" x2="2.7686" y2="-1.016" width="0.127" layer="21"/>
<wire x1="2.7686" y1="-1.016" x2="1.016" y2="-1.016" width="0.127" layer="21"/>
<wire x1="2.9972" y1="0" x2="3.3528" y2="0" width="0.127" layer="21"/>
<wire x1="-1.016" y1="-1.016" x2="-2.7686" y2="-1.016" width="0.127" layer="21"/>
<wire x1="-2.7686" y1="-1.016" x2="-2.7686" y2="1.016" width="0.127" layer="21"/>
<wire x1="-2.7686" y1="1.016" x2="-1.016" y2="1.016" width="0.127" layer="21"/>
<wire x1="-2.9972" y1="0" x2="-3.3528" y2="0" width="0.127" layer="21"/>
<wire x1="-3.175" y1="0.1778" x2="-3.175" y2="-0.1778" width="0.127" layer="21"/>
<text x="-2.54" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="LED">
<wire x1="1.27" y1="0" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-2.032" y1="-0.762" x2="-3.429" y2="-2.159" width="0.1524" layer="94"/>
<wire x1="-1.905" y1="-1.905" x2="-3.302" y2="-3.302" width="0.1524" layer="94"/>
<text x="3.556" y="-4.572" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="5.715" y="-4.572" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="C" x="0" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="A" x="0" y="2.54" visible="off" length="short" direction="pas" rot="R270"/>
<polygon width="0.1524" layer="94">
<vertex x="-3.429" y="-2.159"/>
<vertex x="-3.048" y="-1.27"/>
<vertex x="-2.54" y="-1.778"/>
</polygon>
<polygon width="0.1524" layer="94">
<vertex x="-3.302" y="-3.302"/>
<vertex x="-2.921" y="-2.413"/>
<vertex x="-2.413" y="-2.921"/>
</polygon>
</symbol>
</symbols>
<devicesets>
<deviceset name="LED" prefix="D" uservalue="yes">
<description>&lt;b&gt;LEDs&lt;/b&gt;
Standard schematic elements and footprints for 5mm, 3mm, 1206, and 0603 sized LEDs. 5mm - Spark Fun Electronics SKU : COM-00529 (and others)</description>
<gates>
<gate name="G$1" symbol="LED" x="0" y="0"/>
</gates>
<devices>
<device name="5MM" package="LED5MM">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="K"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3MM" package="LED3MM">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="K"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206" package="LED-1206">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603" package="LED-0603">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="10MM" package="LED10MM">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-FKIT-1206" package="FKIT-LED-1206">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-3MM-NO_SILK" package="LED3MM-NS">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="K"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="5MM-KIT" package="LED5MM-KIT">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="K"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206-BOTTOM" package="LED-1206-BOTTOM">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Passives">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find resistors, capacitors, inductors, test points, jumper pads, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="FUSE_5MM">
<wire x1="-3.2258" y1="-10.127" x2="-3.2258" y2="-4.1072" width="0.2032" layer="21"/>
<wire x1="-3.2258" y1="-10.127" x2="3.2258" y2="-10.127" width="0.2032" layer="21"/>
<wire x1="3.2258" y1="-10.127" x2="3.2258" y2="-4.031" width="0.2032" layer="21"/>
<wire x1="3.2258" y1="-4.031" x2="-3.2258" y2="-4.031" width="0.2032" layer="21"/>
<wire x1="3.2258" y1="10.127" x2="3.2258" y2="4.1072" width="0.2032" layer="21"/>
<wire x1="3.2258" y1="10.127" x2="-3.2258" y2="10.127" width="0.2032" layer="21"/>
<wire x1="-3.2258" y1="10.127" x2="-3.2258" y2="4.031" width="0.2032" layer="21"/>
<wire x1="-3.2258" y1="4.031" x2="3.2258" y2="4.031" width="0.2032" layer="21"/>
<wire x1="-2.921" y1="9.812" x2="-2.921" y2="-9.619" width="0.2032" layer="51"/>
<wire x1="-2.921" y1="-9.619" x2="0.254" y2="-9.619" width="0.2032" layer="51"/>
<wire x1="0.254" y1="-9.619" x2="2.794" y2="-9.619" width="0.2032" layer="51"/>
<wire x1="2.794" y1="-9.619" x2="2.794" y2="9.177" width="0.2032" layer="51"/>
<wire x1="2.794" y1="9.177" x2="2.794" y2="9.812" width="0.2032" layer="51"/>
<wire x1="2.794" y1="9.812" x2="-2.921" y2="9.812" width="0.2032" layer="51"/>
<pad name="1" x="0" y="-10" drill="2.54" diameter="3.556"/>
<pad name="2" x="0" y="-4.158" drill="2.54" diameter="3.556"/>
<pad name="4" x="0" y="10" drill="2.54" diameter="3.556" rot="R180"/>
<pad name="3" x="0" y="4.158" drill="2.54" diameter="3.556" rot="R180"/>
</package>
</packages>
<symbols>
<symbol name="FUSE">
<wire x1="0" y1="0" x2="-5.08" y2="0" width="0.254" layer="94" curve="-180"/>
<wire x1="0" y1="0" x2="5.08" y2="0" width="0.254" layer="94" curve="-180"/>
<text x="-10.16" y="2.54" size="1.27" layer="95">&gt;Name</text>
<text x="5.08" y="2.54" size="1.27" layer="96">&gt;Value</text>
<pin name="1" x="-10.16" y="0" length="middle"/>
<pin name="2" x="10.16" y="0" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="FUSE" prefix="F">
<gates>
<gate name="G$1" symbol="FUSE" x="0" y="0"/>
</gates>
<devices>
<device name="X20MM" package="FUSE_5MM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$2" library="Teensy_3_Series_Chip_v1.2" deviceset="MK20DX256VLH7" device=""/>
<part name="U$3" library="Teensy_3_Series_Chip_v1.2" deviceset="MINI54TAN" device="DEFAULT"/>
<part name="C1" library="SparkFun-Capacitors" deviceset="CAP_POL" device="1206" value="0.1uF"/>
<part name="C2" library="SparkFun-Capacitors" deviceset="CAP_POL" device="1206"/>
<part name="C3" library="SparkFun-Capacitors" deviceset="CAP_POL" device="1206"/>
<part name="C4" library="SparkFun-Capacitors" deviceset="CAP_POL" device="1206" value="0.1uF"/>
<part name="C5" library="SparkFun-Capacitors" deviceset="CAP_POL" device="1206" value="0.1uF"/>
<part name="C6" library="SparkFun-Capacitors" deviceset="CAP_POL" device="1206"/>
<part name="GND-ISO1" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO2" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO3" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO4" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO5" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO6" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO7" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO8" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO9" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO10" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO11" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO12" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO13" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="GND-ISO14" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="C7" library="SparkFun-Capacitors" deviceset="CAP_POL" device="1206" value="0.1uF"/>
<part name="C8" library="SparkFun-Capacitors" deviceset="CAP_POL" device="1206" value="0.1uF"/>
<part name="C9" library="SparkFun-Capacitors" deviceset="CAP_POL" device="1206" value="0.1uF"/>
<part name="C10" library="SparkFun-Capacitors" deviceset="CAP_POL" device="1206" value="2.2uF"/>
<part name="JP2" library="SparkFun-Connectors" deviceset="M06" device="LOCK"/>
<part name="JP3" library="SparkFun-Connectors" deviceset="M06" device="LOCK"/>
<part name="JP4" library="SparkFun-Connectors" deviceset="M06" device="LOCK"/>
<part name="JP5" library="SparkFun-Connectors" deviceset="M06" device="LOCK"/>
<part name="JP6" library="SparkFun-Connectors" deviceset="M06" device="LOCK"/>
<part name="R1" library="SparkFun-Resistors" deviceset="RESISTOR" device="0603" value="470"/>
<part name="FERRITE1" library="inductors" deviceset="BLM15H" device="" technology="B121SN1"/>
<part name="JP7" library="SparkFun-Connectors" deviceset="M06" device="LOCK"/>
<part name="JP1" library="SparkFun-Connectors" deviceset="USB_MICROB_PLUG" device="CONN-11752"/>
<part name="FERRITE2" library="inductors" deviceset="BLM15H" device="" technology="B121SN1"/>
<part name="JP8" library="SparkFun-Connectors" deviceset="M06" device="LOCK"/>
<part name="S1" library="SparkFun-Electromechanical" deviceset="SWITCH-MOMENTARY-2" device="SMD"/>
<part name="R2" library="SparkFun-Resistors" deviceset="RESISTOR" device="0603" value="33"/>
<part name="R3" library="SparkFun-Resistors" deviceset="RESISTOR" device="0603" value="33"/>
<part name="GND-ISO15" library="SparkFun-Aesthetics" deviceset="GND-ISO" device=""/>
<part name="FERRITE3" library="inductors" deviceset="BLM15H" device="" technology="B121SN1"/>
<part name="Y1" library="SparkFun-FreqCtrl" deviceset="CRYSTAL" device="5X3" value="16 MHz"/>
<part name="Y2" library="SparkFun-FreqCtrl" deviceset="CRYSTAL" device="5X3" value="32.768 kHz"/>
<part name="JP9" library="SparkFun-Connectors" deviceset="M06" device="LOCK"/>
<part name="JP10" library="SparkFun-Connectors" deviceset="M06" device="LOCK"/>
<part name="D4" library="SparkFun-LED" deviceset="LED" device="0603"/>
<part name="JP11" library="SparkFun-Connectors" deviceset="M06" device="FEMALE_LOCK"/>
<part name="JP12" library="SparkFun-Connectors" deviceset="M06" device="LOCK"/>
<part name="F1" library="SparkFun-Passives" deviceset="FUSE" device="X20MM" value="500mA"/>
<part name="D6" library="SparkFun-DiscreteSemi" deviceset="DIODE" device="BAS16" value="1A"/>
<part name="D7" library="SparkFun-DiscreteSemi" deviceset="DIODE" device="BAS16" value="1A"/>
<part name="D8" library="SparkFun-DiscreteSemi" deviceset="DIODE" device="BAS16" value="1A"/>
<part name="D9" library="SparkFun-DiscreteSemi" deviceset="DIODE" device="BAS16" value="1A"/>
<part name="FRAME2" library="SparkFun-Aesthetics" deviceset="FRAME-LEDGER" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$2" gate="G$1" x="142.24" y="114.3" rot="MR0"/>
<instance part="U$3" gate="G$1" x="66.04" y="81.28"/>
<instance part="C1" gate="G$1" x="66.04" y="172.72" rot="R270"/>
<instance part="C2" gate="G$1" x="55.88" y="119.38"/>
<instance part="C3" gate="G$1" x="17.78" y="167.64" rot="R180"/>
<instance part="C4" gate="G$1" x="86.36" y="127"/>
<instance part="C5" gate="G$1" x="76.2" y="127"/>
<instance part="C6" gate="G$1" x="38.1" y="144.78"/>
<instance part="GND-ISO1" gate="G$1" x="195.58" y="40.64"/>
<instance part="GND-ISO2" gate="G$1" x="185.42" y="40.64"/>
<instance part="GND-ISO3" gate="G$1" x="111.76" y="22.86"/>
<instance part="GND-ISO4" gate="G$1" x="45.72" y="48.26"/>
<instance part="GND-ISO5" gate="G$1" x="10.16" y="76.2"/>
<instance part="GND-ISO6" gate="G$1" x="2.54" y="104.14"/>
<instance part="GND-ISO7" gate="G$1" x="25.4" y="109.22"/>
<instance part="GND-ISO8" gate="G$1" x="55.88" y="106.68"/>
<instance part="GND-ISO9" gate="G$1" x="63.5" y="147.32"/>
<instance part="GND-ISO10" gate="G$1" x="73.66" y="147.32"/>
<instance part="GND-ISO11" gate="G$1" x="83.82" y="147.32"/>
<instance part="GND-ISO12" gate="G$1" x="91.44" y="147.32"/>
<instance part="GND-ISO13" gate="G$1" x="17.78" y="177.8" rot="R180"/>
<instance part="GND-ISO14" gate="G$1" x="53.34" y="172.72" rot="R270"/>
<instance part="C7" gate="G$1" x="63.5" y="157.48"/>
<instance part="C8" gate="G$1" x="73.66" y="157.48"/>
<instance part="C9" gate="G$1" x="83.82" y="157.48"/>
<instance part="C10" gate="G$1" x="91.44" y="157.48"/>
<instance part="JP2" gate="G$1" x="220.98" y="167.64" rot="R180"/>
<instance part="JP3" gate="G$1" x="220.98" y="147.32" rot="R180"/>
<instance part="JP4" gate="G$1" x="220.98" y="127" rot="R180"/>
<instance part="JP5" gate="G$1" x="220.98" y="86.36" rot="R180"/>
<instance part="JP6" gate="G$1" x="220.98" y="66.04" rot="R180"/>
<instance part="R1" gate="G$1" x="71.12" y="134.62"/>
<instance part="FERRITE1" gate="G$1" x="53.34" y="154.94" rot="R270"/>
<instance part="JP7" gate="G$1" x="7.62" y="88.9"/>
<instance part="JP1" gate="G$1" x="10.16" y="127" rot="MR0"/>
<instance part="FERRITE2" gate="G$1" x="2.54" y="114.3" rot="R90"/>
<instance part="JP8" gate="G$1" x="7.62" y="149.86"/>
<instance part="S1" gate="G$1" x="22.86" y="76.2" rot="R90"/>
<instance part="R2" gate="G$1" x="86.36" y="35.56"/>
<instance part="R3" gate="G$1" x="86.36" y="25.4"/>
<instance part="GND-ISO15" gate="G$1" x="20.32" y="137.16" rot="R270"/>
<instance part="FERRITE3" gate="G$1" x="30.48" y="137.16"/>
<instance part="Y1" gate="G$1" x="111.76" y="78.74" rot="R90"/>
<instance part="Y2" gate="G$1" x="101.6" y="106.68" rot="R90"/>
<instance part="JP9" gate="G$1" x="220.98" y="45.72" rot="R180"/>
<instance part="JP10" gate="G$1" x="220.98" y="106.68" rot="R180"/>
<instance part="D4" gate="G$1" x="185.42" y="48.26"/>
<instance part="JP11" gate="G$1" x="238.76" y="101.6" rot="R180"/>
<instance part="JP12" gate="G$1" x="7.62" y="175.26"/>
<instance part="F1" gate="G$1" x="40.64" y="165.1" rot="R90"/>
<instance part="D6" gate="G$1" x="58.42" y="127" rot="R270"/>
<instance part="D7" gate="G$1" x="53.34" y="127" rot="R270"/>
<instance part="D8" gate="G$1" x="91.44" y="175.26" rot="R270"/>
<instance part="D9" gate="G$1" x="86.36" y="175.26" rot="R270"/>
<instance part="FRAME2" gate="G$1" x="-22.86" y="-33.02"/>
<instance part="FRAME2" gate="G$2" x="307.34" y="-33.02"/>
</instances>
<busses>
</busses>
<nets>
<net name="3.3V" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="VCC"/>
<wire x1="111.76" y1="162.56" x2="106.68" y2="162.56" width="0.1524" layer="91"/>
<pinref part="C7" gate="G$1" pin="+"/>
<wire x1="106.68" y1="162.56" x2="91.44" y2="162.56" width="0.1524" layer="91"/>
<wire x1="91.44" y1="162.56" x2="83.82" y2="162.56" width="0.1524" layer="91"/>
<wire x1="83.82" y1="162.56" x2="73.66" y2="162.56" width="0.1524" layer="91"/>
<wire x1="73.66" y1="162.56" x2="63.5" y2="162.56" width="0.1524" layer="91"/>
<wire x1="63.5" y1="162.56" x2="53.34" y2="162.56" width="0.1524" layer="91"/>
<wire x1="53.34" y1="162.56" x2="33.02" y2="162.56" width="0.1524" layer="91"/>
<wire x1="63.5" y1="162.56" x2="63.5" y2="160.02" width="0.1524" layer="91"/>
<junction x="63.5" y="162.56"/>
<pinref part="C8" gate="G$1" pin="+"/>
<wire x1="73.66" y1="162.56" x2="73.66" y2="160.02" width="0.1524" layer="91"/>
<junction x="73.66" y="162.56"/>
<pinref part="C9" gate="G$1" pin="+"/>
<wire x1="83.82" y1="162.56" x2="83.82" y2="160.02" width="0.1524" layer="91"/>
<junction x="83.82" y="162.56"/>
<pinref part="C10" gate="G$1" pin="+"/>
<wire x1="91.44" y1="162.56" x2="91.44" y2="160.02" width="0.1524" layer="91"/>
<junction x="91.44" y="162.56"/>
<pinref part="U$2" gate="G$1" pin="VOUT3V3"/>
<wire x1="111.76" y1="165.1" x2="106.68" y2="165.1" width="0.1524" layer="91"/>
<wire x1="106.68" y1="165.1" x2="106.68" y2="162.56" width="0.1524" layer="91"/>
<junction x="106.68" y="162.56"/>
<wire x1="106.68" y1="165.1" x2="106.68" y2="175.26" width="0.1524" layer="91"/>
<wire x1="106.68" y1="175.26" x2="185.42" y2="175.26" width="0.1524" layer="91"/>
<junction x="106.68" y="165.1"/>
<wire x1="185.42" y1="175.26" x2="185.42" y2="167.64" width="0.1524" layer="91"/>
<pinref part="JP2" gate="G$1" pin="3"/>
<wire x1="185.42" y1="167.64" x2="213.36" y2="167.64" width="0.1524" layer="91"/>
<label x="220.98" y="167.64" size="1.778" layer="95"/>
<pinref part="JP7" gate="G$1" pin="2"/>
<wire x1="213.36" y1="167.64" x2="215.9" y2="167.64" width="0.1524" layer="91"/>
<wire x1="33.02" y1="162.56" x2="33.02" y2="132.08" width="0.1524" layer="91"/>
<wire x1="33.02" y1="132.08" x2="33.02" y2="86.36" width="0.1524" layer="91"/>
<wire x1="33.02" y1="86.36" x2="12.7" y2="86.36" width="0.1524" layer="91"/>
<label x="2.54" y="86.36" size="1.778" layer="95"/>
<wire x1="33.02" y1="132.08" x2="58.42" y2="132.08" width="0.1524" layer="91"/>
<wire x1="58.42" y1="132.08" x2="58.42" y2="129.54" width="0.1524" layer="91"/>
<junction x="33.02" y="132.08"/>
<wire x1="33.02" y1="86.36" x2="45.72" y2="86.36" width="0.1524" layer="91"/>
<wire x1="45.72" y1="86.36" x2="45.72" y2="96.52" width="0.1524" layer="91"/>
<junction x="33.02" y="86.36"/>
<pinref part="U$3" gate="G$1" pin="VDD"/>
<wire x1="45.72" y1="96.52" x2="48.26" y2="96.52" width="0.1524" layer="91"/>
<pinref part="FERRITE1" gate="G$1" pin="1"/>
<wire x1="53.34" y1="162.56" x2="53.34" y2="160.02" width="0.1524" layer="91"/>
<junction x="53.34" y="162.56"/>
<pinref part="JP5" gate="G$1" pin="4"/>
<wire x1="213.36" y1="167.64" x2="213.36" y2="83.82" width="0.1524" layer="91"/>
<wire x1="213.36" y1="83.82" x2="215.9" y2="83.82" width="0.1524" layer="91"/>
<junction x="213.36" y="167.64"/>
<pinref part="D6" gate="G$1" pin="A"/>
</segment>
</net>
<net name="GND-ISO" class="0">
<segment>
<pinref part="C10" gate="G$1" pin="-"/>
<pinref part="GND-ISO12" gate="G$1" pin="GND-ISO"/>
<wire x1="91.44" y1="152.4" x2="91.44" y2="149.86" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C9" gate="G$1" pin="-"/>
<pinref part="GND-ISO11" gate="G$1" pin="GND-ISO"/>
<wire x1="83.82" y1="152.4" x2="83.82" y2="149.86" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C8" gate="G$1" pin="-"/>
<pinref part="GND-ISO10" gate="G$1" pin="GND-ISO"/>
<wire x1="73.66" y1="152.4" x2="73.66" y2="149.86" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C7" gate="G$1" pin="-"/>
<pinref part="GND-ISO9" gate="G$1" pin="GND-ISO"/>
<wire x1="63.5" y1="152.4" x2="63.5" y2="149.86" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C1" gate="G$1" pin="-"/>
<pinref part="GND-ISO14" gate="G$1" pin="GND-ISO"/>
<wire x1="60.96" y1="172.72" x2="55.88" y2="172.72" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP7" gate="G$1" pin="3"/>
<wire x1="12.7" y1="88.9" x2="15.24" y2="88.9" width="0.1524" layer="91"/>
<wire x1="15.24" y1="88.9" x2="15.24" y2="81.28" width="0.1524" layer="91"/>
<pinref part="GND-ISO5" gate="G$1" pin="GND-ISO"/>
<wire x1="15.24" y1="81.28" x2="10.16" y2="81.28" width="0.1524" layer="91"/>
<wire x1="10.16" y1="81.28" x2="10.16" y2="78.74" width="0.1524" layer="91"/>
<label x="2.54" y="88.9" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FERRITE2" gate="G$1" pin="1"/>
<pinref part="GND-ISO6" gate="G$1" pin="GND-ISO"/>
<wire x1="2.54" y1="109.22" x2="2.54" y2="106.68" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP1" gate="G$1" pin="GND"/>
<pinref part="GND-ISO7" gate="G$1" pin="GND-ISO"/>
<wire x1="17.78" y1="121.92" x2="25.4" y2="121.92" width="0.1524" layer="91"/>
<wire x1="25.4" y1="121.92" x2="25.4" y2="111.76" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C2" gate="G$1" pin="-"/>
<pinref part="GND-ISO8" gate="G$1" pin="GND-ISO"/>
<wire x1="55.88" y1="114.3" x2="55.88" y2="111.76" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="VBAT"/>
<wire x1="55.88" y1="111.76" x2="55.88" y2="109.22" width="0.1524" layer="91"/>
<wire x1="55.88" y1="111.76" x2="111.76" y2="111.76" width="0.1524" layer="91"/>
<wire x1="111.76" y1="111.76" x2="111.76" y2="114.3" width="0.1524" layer="91"/>
<junction x="55.88" y="111.76"/>
</segment>
<segment>
<pinref part="S1" gate="G$1" pin="1"/>
<wire x1="22.86" y1="71.12" x2="27.94" y2="71.12" width="0.1524" layer="91"/>
<wire x1="27.94" y1="71.12" x2="27.94" y2="73.66" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="VSS"/>
<wire x1="27.94" y1="73.66" x2="45.72" y2="73.66" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P2.5"/>
<wire x1="45.72" y1="73.66" x2="48.26" y2="73.66" width="0.1524" layer="91"/>
<wire x1="45.72" y1="73.66" x2="45.72" y2="71.12" width="0.1524" layer="91"/>
<wire x1="45.72" y1="71.12" x2="48.26" y2="71.12" width="0.1524" layer="91"/>
<junction x="45.72" y="73.66"/>
<pinref part="U$3" gate="G$1" pin="P1.4"/>
<wire x1="45.72" y1="71.12" x2="45.72" y2="68.58" width="0.1524" layer="91"/>
<wire x1="45.72" y1="68.58" x2="48.26" y2="68.58" width="0.1524" layer="91"/>
<junction x="45.72" y="71.12"/>
<pinref part="GND-ISO4" gate="G$1" pin="GND-ISO"/>
<wire x1="45.72" y1="68.58" x2="45.72" y2="50.8" width="0.1524" layer="91"/>
<junction x="45.72" y="68.58"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="VSS"/>
<wire x1="111.76" y1="119.38" x2="109.22" y2="119.38" width="0.1524" layer="91"/>
<wire x1="109.22" y1="119.38" x2="109.22" y2="27.94" width="0.1524" layer="91"/>
<pinref part="GND-ISO3" gate="G$1" pin="GND-ISO"/>
<wire x1="109.22" y1="27.94" x2="111.76" y2="27.94" width="0.1524" layer="91"/>
<wire x1="111.76" y1="27.94" x2="111.76" y2="25.4" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND-ISO15" gate="G$1" pin="GND-ISO"/>
<pinref part="FERRITE3" gate="G$1" pin="1"/>
<wire x1="22.86" y1="137.16" x2="25.4" y2="137.16" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND-ISO2" gate="G$1" pin="GND-ISO"/>
<pinref part="D4" gate="G$1" pin="C"/>
</segment>
<segment>
<pinref part="JP5" gate="G$1" pin="2"/>
<pinref part="GND-ISO1" gate="G$1" pin="GND-ISO"/>
<wire x1="215.9" y1="88.9" x2="195.58" y2="88.9" width="0.1524" layer="91"/>
<wire x1="195.58" y1="88.9" x2="195.58" y2="45.72" width="0.1524" layer="91"/>
<pinref part="JP9" gate="G$1" pin="3"/>
<wire x1="195.58" y1="45.72" x2="195.58" y2="43.18" width="0.1524" layer="91"/>
<wire x1="195.58" y1="45.72" x2="215.9" y2="45.72" width="0.1524" layer="91"/>
<junction x="195.58" y="45.72"/>
</segment>
<segment>
<pinref part="GND-ISO13" gate="G$1" pin="GND-ISO"/>
<pinref part="C3" gate="G$1" pin="-"/>
<wire x1="17.78" y1="175.26" x2="17.78" y2="172.72" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="VREGIN"/>
<wire x1="111.76" y1="167.64" x2="88.9" y2="167.64" width="0.1524" layer="91"/>
<wire x1="88.9" y1="167.64" x2="76.2" y2="167.64" width="0.1524" layer="91"/>
<wire x1="76.2" y1="167.64" x2="76.2" y2="172.72" width="0.1524" layer="91"/>
<pinref part="C1" gate="G$1" pin="+"/>
<wire x1="76.2" y1="172.72" x2="68.58" y2="172.72" width="0.1524" layer="91"/>
<wire x1="88.9" y1="167.64" x2="88.9" y2="172.72" width="0.1524" layer="91"/>
<junction x="88.9" y="167.64"/>
<wire x1="88.9" y1="172.72" x2="86.36" y2="172.72" width="0.1524" layer="91"/>
<wire x1="88.9" y1="172.72" x2="91.44" y2="172.72" width="0.1524" layer="91"/>
<junction x="88.9" y="172.72"/>
<pinref part="D8" gate="G$1" pin="C"/>
<pinref part="D9" gate="G$1" pin="C"/>
</segment>
</net>
<net name="VIN" class="0">
<segment>
<wire x1="86.36" y1="177.8" x2="86.36" y2="182.88" width="0.1524" layer="91"/>
<wire x1="86.36" y1="182.88" x2="91.44" y2="182.88" width="0.1524" layer="91"/>
<wire x1="91.44" y1="182.88" x2="91.44" y2="177.8" width="0.1524" layer="91"/>
<wire x1="91.44" y1="182.88" x2="195.58" y2="182.88" width="0.1524" layer="91"/>
<wire x1="195.58" y1="182.88" x2="195.58" y2="172.72" width="0.1524" layer="91"/>
<junction x="91.44" y="182.88"/>
<pinref part="JP2" gate="G$1" pin="1"/>
<wire x1="195.58" y1="172.72" x2="215.9" y2="172.72" width="0.1524" layer="91"/>
<label x="220.98" y="172.72" size="1.778" layer="95"/>
<pinref part="D8" gate="G$1" pin="A"/>
<pinref part="D9" gate="G$1" pin="A"/>
<pinref part="JP12" gate="G$1" pin="6"/>
<pinref part="F1" gate="G$1" pin="2"/>
<wire x1="12.7" y1="182.88" x2="40.64" y2="182.88" width="0.1524" layer="91"/>
<wire x1="40.64" y1="182.88" x2="40.64" y2="175.26" width="0.1524" layer="91"/>
<wire x1="40.64" y1="182.88" x2="86.36" y2="182.88" width="0.1524" layer="91"/>
<junction x="40.64" y="182.88"/>
<junction x="86.36" y="182.88"/>
</segment>
</net>
<net name="AGND" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="VREF-L"/>
<wire x1="111.76" y1="129.54" x2="106.68" y2="129.54" width="0.1524" layer="91"/>
<wire x1="106.68" y1="129.54" x2="106.68" y2="127" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="VSSA"/>
<wire x1="106.68" y1="127" x2="111.76" y2="127" width="0.1524" layer="91"/>
<wire x1="106.68" y1="127" x2="106.68" y2="121.92" width="0.1524" layer="91"/>
<junction x="106.68" y="127"/>
<wire x1="106.68" y1="121.92" x2="106.68" y2="55.88" width="0.1524" layer="91"/>
<wire x1="106.68" y1="55.88" x2="190.5" y2="55.88" width="0.1524" layer="91"/>
<wire x1="190.5" y1="55.88" x2="190.5" y2="170.18" width="0.1524" layer="91"/>
<pinref part="JP2" gate="G$1" pin="2"/>
<wire x1="190.5" y1="170.18" x2="215.9" y2="170.18" width="0.1524" layer="91"/>
<label x="220.98" y="170.18" size="1.778" layer="95"/>
<pinref part="C4" gate="G$1" pin="-"/>
<wire x1="106.68" y1="121.92" x2="86.36" y2="121.92" width="0.1524" layer="91"/>
<junction x="106.68" y="121.92"/>
<pinref part="C5" gate="G$1" pin="-"/>
<wire x1="86.36" y1="121.92" x2="76.2" y2="121.92" width="0.1524" layer="91"/>
<junction x="86.36" y="121.92"/>
<wire x1="76.2" y1="121.92" x2="63.5" y2="121.92" width="0.1524" layer="91"/>
<wire x1="63.5" y1="121.92" x2="63.5" y2="137.16" width="0.1524" layer="91"/>
<junction x="76.2" y="121.92"/>
<pinref part="C6" gate="G$1" pin="-"/>
<wire x1="63.5" y1="137.16" x2="38.1" y2="137.16" width="0.1524" layer="91"/>
<wire x1="38.1" y1="137.16" x2="38.1" y2="139.7" width="0.1524" layer="91"/>
<pinref part="FERRITE3" gate="G$1" pin="2"/>
<wire x1="35.56" y1="137.16" x2="38.1" y2="137.16" width="0.1524" layer="91"/>
<junction x="38.1" y="137.16"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="C4" gate="G$1" pin="+"/>
<pinref part="U$2" gate="G$1" pin="VREF_OUT"/>
<wire x1="86.36" y1="129.54" x2="86.36" y2="139.7" width="0.1524" layer="91"/>
<wire x1="86.36" y1="139.7" x2="111.76" y2="139.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="VREF-H"/>
<wire x1="106.68" y1="142.24" x2="106.68" y2="149.86" width="0.1524" layer="91"/>
<wire x1="106.68" y1="149.86" x2="111.76" y2="149.86" width="0.1524" layer="91"/>
<wire x1="106.68" y1="142.24" x2="76.2" y2="142.24" width="0.1524" layer="91"/>
<wire x1="76.2" y1="142.24" x2="76.2" y2="134.62" width="0.1524" layer="91"/>
<wire x1="76.2" y1="142.24" x2="45.72" y2="142.24" width="0.1524" layer="91"/>
<wire x1="45.72" y1="142.24" x2="45.72" y2="152.4" width="0.1524" layer="91"/>
<junction x="76.2" y="142.24"/>
<pinref part="JP8" gate="G$1" pin="4"/>
<wire x1="45.72" y1="152.4" x2="12.7" y2="152.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="VCCA"/>
<wire x1="111.76" y1="152.4" x2="109.22" y2="152.4" width="0.1524" layer="91"/>
<wire x1="109.22" y1="152.4" x2="109.22" y2="144.78" width="0.1524" layer="91"/>
<wire x1="109.22" y1="144.78" x2="66.04" y2="144.78" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="66.04" y1="144.78" x2="66.04" y2="139.7" width="0.1524" layer="91"/>
<pinref part="FERRITE1" gate="G$1" pin="2"/>
<wire x1="66.04" y1="139.7" x2="66.04" y2="134.62" width="0.1524" layer="91"/>
<wire x1="66.04" y1="139.7" x2="53.34" y2="139.7" width="0.1524" layer="91"/>
<wire x1="53.34" y1="139.7" x2="53.34" y2="149.86" width="0.1524" layer="91"/>
<junction x="66.04" y="139.7"/>
<pinref part="C6" gate="G$1" pin="+"/>
<wire x1="53.34" y1="149.86" x2="38.1" y2="149.86" width="0.1524" layer="91"/>
<wire x1="38.1" y1="149.86" x2="38.1" y2="147.32" width="0.1524" layer="91"/>
<junction x="53.34" y="149.86"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="2"/>
<pinref part="C5" gate="G$1" pin="+"/>
<wire x1="76.2" y1="129.54" x2="76.2" y2="134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="SHIELD"/>
<pinref part="FERRITE2" gate="G$1" pin="2"/>
<wire x1="2.54" y1="127" x2="2.54" y2="119.38" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="C2" gate="G$1" pin="+"/>
<wire x1="58.42" y1="124.46" x2="55.88" y2="124.46" width="0.1524" layer="91"/>
<wire x1="55.88" y1="124.46" x2="55.88" y2="121.92" width="0.1524" layer="91"/>
<wire x1="53.34" y1="124.46" x2="55.88" y2="124.46" width="0.1524" layer="91"/>
<junction x="55.88" y="124.46"/>
<pinref part="D6" gate="G$1" pin="C"/>
<pinref part="D7" gate="G$1" pin="C"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="JP7" gate="G$1" pin="1"/>
<wire x1="12.7" y1="83.82" x2="43.18" y2="83.82" width="0.1524" layer="91"/>
<wire x1="43.18" y1="83.82" x2="43.18" y2="129.54" width="0.1524" layer="91"/>
<wire x1="43.18" y1="129.54" x2="53.34" y2="129.54" width="0.1524" layer="91"/>
<pinref part="D7" gate="G$1" pin="A"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="JP7" gate="G$1" pin="4"/>
<pinref part="U$3" gate="G$1" pin="P5.2"/>
<wire x1="12.7" y1="91.44" x2="22.86" y2="91.44" width="0.1524" layer="91"/>
<wire x1="22.86" y1="91.44" x2="48.26" y2="91.44" width="0.1524" layer="91"/>
<wire x1="48.26" y1="91.44" x2="48.26" y2="88.9" width="0.1524" layer="91"/>
<pinref part="S1" gate="G$1" pin="2"/>
<wire x1="22.86" y1="91.44" x2="22.86" y2="81.28" width="0.1524" layer="91"/>
<junction x="22.86" y="91.44"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="JP7" gate="G$1" pin="5"/>
<wire x1="12.7" y1="93.98" x2="40.64" y2="93.98" width="0.1524" layer="91"/>
<wire x1="40.64" y1="93.98" x2="40.64" y2="81.28" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P3.2"/>
<wire x1="40.64" y1="81.28" x2="48.26" y2="81.28" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="RESET"/>
<wire x1="111.76" y1="99.06" x2="96.52" y2="99.06" width="0.1524" layer="91"/>
<wire x1="96.52" y1="99.06" x2="96.52" y2="55.88" width="0.1524" layer="91"/>
<wire x1="96.52" y1="55.88" x2="40.64" y2="55.88" width="0.1524" layer="91"/>
<wire x1="40.64" y1="55.88" x2="40.64" y2="81.28" width="0.1524" layer="91"/>
<junction x="40.64" y="81.28"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="ID"/>
<wire x1="17.78" y1="124.46" x2="48.26" y2="124.46" width="0.1524" layer="91"/>
<wire x1="48.26" y1="124.46" x2="48.26" y2="104.14" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P0.0"/>
<wire x1="48.26" y1="104.14" x2="83.82" y2="104.14" width="0.1524" layer="91"/>
<wire x1="83.82" y1="104.14" x2="83.82" y2="96.52" width="0.1524" layer="91"/>
<wire x1="83.82" y1="96.52" x2="101.6" y2="96.52" width="0.1524" layer="91"/>
<wire x1="101.6" y1="96.52" x2="101.6" y2="93.98" width="0.1524" layer="91"/>
<junction x="83.82" y="96.52"/>
<pinref part="U$2" gate="G$1" pin="PTA1"/>
<wire x1="101.6" y1="93.98" x2="111.76" y2="93.98" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="P0.6"/>
<wire x1="83.82" y1="93.98" x2="88.9" y2="93.98" width="0.1524" layer="91"/>
<wire x1="88.9" y1="93.98" x2="88.9" y2="91.44" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P0.5"/>
<wire x1="88.9" y1="91.44" x2="83.82" y2="91.44" width="0.1524" layer="91"/>
<wire x1="88.9" y1="91.44" x2="93.98" y2="91.44" width="0.1524" layer="91"/>
<wire x1="93.98" y1="91.44" x2="93.98" y2="88.9" width="0.1524" layer="91"/>
<junction x="88.9" y="91.44"/>
<pinref part="U$2" gate="G$1" pin="PTA3"/>
<wire x1="93.98" y1="88.9" x2="111.76" y2="88.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="P0.7"/>
<wire x1="83.82" y1="88.9" x2="91.44" y2="88.9" width="0.1524" layer="91"/>
<wire x1="91.44" y1="88.9" x2="91.44" y2="93.98" width="0.1524" layer="91"/>
<wire x1="91.44" y1="93.98" x2="99.06" y2="93.98" width="0.1524" layer="91"/>
<wire x1="99.06" y1="93.98" x2="99.06" y2="91.44" width="0.1524" layer="91"/>
<wire x1="99.06" y1="91.44" x2="104.14" y2="91.44" width="0.1524" layer="91"/>
<wire x1="104.14" y1="91.44" x2="104.14" y2="96.52" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="PTA0"/>
<wire x1="104.14" y1="96.52" x2="111.76" y2="96.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="PTA2"/>
<wire x1="111.76" y1="91.44" x2="109.22" y2="91.44" width="0.1524" layer="91"/>
<wire x1="109.22" y1="91.44" x2="109.22" y2="86.36" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P0.1"/>
<wire x1="109.22" y1="86.36" x2="83.82" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D18/A4/SDA0/TOUCH"/>
<wire x1="170.18" y1="119.38" x2="177.8" y2="119.38" width="0.1524" layer="91"/>
<wire x1="177.8" y1="119.38" x2="177.8" y2="58.42" width="0.1524" layer="91"/>
<wire x1="177.8" y1="58.42" x2="104.14" y2="58.42" width="0.1524" layer="91"/>
<wire x1="104.14" y1="58.42" x2="104.14" y2="71.12" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P3.4"/>
<wire x1="104.14" y1="71.12" x2="83.82" y2="71.12" width="0.1524" layer="91"/>
<pinref part="JP3" gate="G$1" pin="3"/>
<wire x1="177.8" y1="119.38" x2="177.8" y2="147.32" width="0.1524" layer="91"/>
<wire x1="177.8" y1="147.32" x2="215.9" y2="147.32" width="0.1524" layer="91"/>
<junction x="177.8" y="119.38"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="P3.5"/>
<wire x1="83.82" y1="68.58" x2="91.44" y2="68.58" width="0.1524" layer="91"/>
<wire x1="91.44" y1="68.58" x2="91.44" y2="53.34" width="0.1524" layer="91"/>
<wire x1="91.44" y1="53.34" x2="180.34" y2="53.34" width="0.1524" layer="91"/>
<wire x1="180.34" y1="53.34" x2="180.34" y2="116.84" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="D19/A5/SCL0/TOUCH"/>
<wire x1="180.34" y1="116.84" x2="170.18" y2="116.84" width="0.1524" layer="91"/>
<pinref part="JP3" gate="G$1" pin="2"/>
<wire x1="180.34" y1="116.84" x2="180.34" y2="149.86" width="0.1524" layer="91"/>
<wire x1="180.34" y1="149.86" x2="215.9" y2="149.86" width="0.1524" layer="91"/>
<junction x="180.34" y="116.84"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="USB-P"/>
<wire x1="111.76" y1="68.58" x2="101.6" y2="68.58" width="0.1524" layer="91"/>
<wire x1="101.6" y1="68.58" x2="101.6" y2="35.56" width="0.1524" layer="91"/>
<wire x1="101.6" y1="35.56" x2="91.44" y2="35.56" width="0.1524" layer="91"/>
<pinref part="R2" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="USB-M"/>
<wire x1="111.76" y1="66.04" x2="99.06" y2="66.04" width="0.1524" layer="91"/>
<wire x1="99.06" y1="66.04" x2="99.06" y2="25.4" width="0.1524" layer="91"/>
<wire x1="99.06" y1="25.4" x2="91.44" y2="25.4" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="R2" gate="G$1" pin="1"/>
<wire x1="81.28" y1="35.56" x2="20.32" y2="35.56" width="0.1524" layer="91"/>
<wire x1="20.32" y1="35.56" x2="20.32" y2="127" width="0.1524" layer="91"/>
<pinref part="JP1" gate="G$1" pin="D+"/>
<wire x1="20.32" y1="127" x2="17.78" y2="127" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="R3" gate="G$1" pin="1"/>
<wire x1="81.28" y1="25.4" x2="30.48" y2="25.4" width="0.1524" layer="91"/>
<wire x1="30.48" y1="25.4" x2="30.48" y2="129.54" width="0.1524" layer="91"/>
<pinref part="JP1" gate="G$1" pin="D-"/>
<wire x1="30.48" y1="129.54" x2="17.78" y2="129.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="A11/ADC0_DP0"/>
<wire x1="170.18" y1="76.2" x2="182.88" y2="76.2" width="0.1524" layer="91"/>
<wire x1="182.88" y1="76.2" x2="182.88" y2="177.8" width="0.1524" layer="91"/>
<wire x1="182.88" y1="177.8" x2="30.48" y2="177.8" width="0.1524" layer="91"/>
<wire x1="30.48" y1="177.8" x2="30.48" y2="154.94" width="0.1524" layer="91"/>
<pinref part="JP8" gate="G$1" pin="5"/>
<wire x1="30.48" y1="154.94" x2="12.7" y2="154.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="JP8" gate="G$1" pin="6"/>
<wire x1="12.7" y1="157.48" x2="27.94" y2="157.48" width="0.1524" layer="91"/>
<wire x1="27.94" y1="157.48" x2="27.94" y2="180.34" width="0.1524" layer="91"/>
<wire x1="27.94" y1="180.34" x2="175.26" y2="180.34" width="0.1524" layer="91"/>
<wire x1="175.26" y1="180.34" x2="175.26" y2="78.74" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="A10/ADC0_DM0"/>
<wire x1="175.26" y1="78.74" x2="170.18" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="XTAL32"/>
<pinref part="Y2" gate="G$1" pin="2"/>
<wire x1="111.76" y1="109.22" x2="101.6" y2="109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="Y2" gate="G$1" pin="1"/>
<pinref part="U$2" gate="G$1" pin="EXTAL32"/>
<wire x1="101.6" y1="104.14" x2="111.76" y2="104.14" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$25" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="OSC1"/>
<pinref part="Y1" gate="G$1" pin="2"/>
<wire x1="111.76" y1="83.82" x2="111.76" y2="81.28" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$26" class="0">
<segment>
<pinref part="Y1" gate="G$1" pin="1"/>
<pinref part="U$2" gate="G$1" pin="OSC2"/>
<wire x1="111.76" y1="76.2" x2="111.76" y2="73.66" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$27" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D23/A9/PWM/TOUCH"/>
<wire x1="170.18" y1="106.68" x2="185.42" y2="106.68" width="0.1524" layer="91"/>
<wire x1="185.42" y1="106.68" x2="185.42" y2="165.1" width="0.1524" layer="91"/>
<pinref part="JP2" gate="G$1" pin="4"/>
<wire x1="185.42" y1="165.1" x2="215.9" y2="165.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$28" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D22/A8/PWM/TOUCH"/>
<wire x1="170.18" y1="109.22" x2="193.04" y2="109.22" width="0.1524" layer="91"/>
<wire x1="193.04" y1="109.22" x2="193.04" y2="162.56" width="0.1524" layer="91"/>
<pinref part="JP2" gate="G$1" pin="5"/>
<wire x1="193.04" y1="162.56" x2="215.9" y2="162.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$29" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D21/A7/PWM"/>
<wire x1="170.18" y1="111.76" x2="187.96" y2="111.76" width="0.1524" layer="91"/>
<wire x1="187.96" y1="111.76" x2="187.96" y2="160.02" width="0.1524" layer="91"/>
<pinref part="JP2" gate="G$1" pin="6"/>
<wire x1="187.96" y1="160.02" x2="215.9" y2="160.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$30" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D20/A6/PWM"/>
<wire x1="170.18" y1="114.3" x2="195.58" y2="114.3" width="0.1524" layer="91"/>
<wire x1="195.58" y1="114.3" x2="195.58" y2="152.4" width="0.1524" layer="91"/>
<pinref part="JP3" gate="G$1" pin="1"/>
<wire x1="195.58" y1="152.4" x2="215.9" y2="152.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$31" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D17/A3/TOUCH"/>
<wire x1="170.18" y1="121.92" x2="198.12" y2="121.92" width="0.1524" layer="91"/>
<wire x1="198.12" y1="121.92" x2="198.12" y2="144.78" width="0.1524" layer="91"/>
<pinref part="JP3" gate="G$1" pin="4"/>
<wire x1="198.12" y1="144.78" x2="215.9" y2="144.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D15/A1/TOUCH"/>
<wire x1="170.18" y1="127" x2="200.66" y2="127" width="0.1524" layer="91"/>
<wire x1="200.66" y1="127" x2="200.66" y2="142.24" width="0.1524" layer="91"/>
<pinref part="JP3" gate="G$1" pin="5"/>
<wire x1="200.66" y1="142.24" x2="215.9" y2="142.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$33" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D14/A0"/>
<wire x1="170.18" y1="129.54" x2="203.2" y2="129.54" width="0.1524" layer="91"/>
<wire x1="203.2" y1="129.54" x2="203.2" y2="139.7" width="0.1524" layer="91"/>
<pinref part="JP3" gate="G$1" pin="6"/>
<wire x1="203.2" y1="139.7" x2="215.9" y2="139.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$34" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D13/SCK/LED"/>
<pinref part="JP4" gate="G$1" pin="1"/>
<wire x1="170.18" y1="132.08" x2="172.72" y2="132.08" width="0.1524" layer="91"/>
<wire x1="172.72" y1="132.08" x2="215.9" y2="132.08" width="0.1524" layer="91"/>
<wire x1="172.72" y1="132.08" x2="172.72" y2="50.8" width="0.1524" layer="91"/>
<wire x1="172.72" y1="50.8" x2="185.42" y2="50.8" width="0.1524" layer="91"/>
<junction x="172.72" y="132.08"/>
<pinref part="D4" gate="G$1" pin="A"/>
</segment>
</net>
<net name="N$35" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D12/MISO"/>
<wire x1="170.18" y1="134.62" x2="213.36" y2="134.62" width="0.1524" layer="91"/>
<wire x1="213.36" y1="134.62" x2="213.36" y2="129.54" width="0.1524" layer="91"/>
<pinref part="JP4" gate="G$1" pin="2"/>
<wire x1="213.36" y1="129.54" x2="215.9" y2="129.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$36" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D11/MOSI"/>
<wire x1="170.18" y1="137.16" x2="210.82" y2="137.16" width="0.1524" layer="91"/>
<wire x1="210.82" y1="137.16" x2="210.82" y2="127" width="0.1524" layer="91"/>
<pinref part="JP4" gate="G$1" pin="3"/>
<wire x1="210.82" y1="127" x2="215.9" y2="127" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$37" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D10/TX2/PWM"/>
<wire x1="170.18" y1="139.7" x2="208.28" y2="139.7" width="0.1524" layer="91"/>
<wire x1="208.28" y1="139.7" x2="208.28" y2="124.46" width="0.1524" layer="91"/>
<pinref part="JP4" gate="G$1" pin="4"/>
<wire x1="208.28" y1="124.46" x2="215.9" y2="124.46" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$38" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D9/RX2/PWM"/>
<wire x1="170.18" y1="142.24" x2="203.2" y2="144.78" width="0.1524" layer="91"/>
<wire x1="203.2" y1="144.78" x2="205.74" y2="121.92" width="0.1524" layer="91"/>
<pinref part="JP4" gate="G$1" pin="5"/>
<wire x1="205.74" y1="121.92" x2="215.9" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$39" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D7/RX3"/>
<wire x1="170.18" y1="147.32" x2="231.14" y2="144.78" width="0.1524" layer="91"/>
<wire x1="231.14" y1="144.78" x2="231.14" y2="116.84" width="0.1524" layer="91"/>
<pinref part="JP4" gate="G$1" pin="6"/>
<wire x1="231.14" y1="116.84" x2="215.9" y2="119.38" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D6/PWM"/>
<wire x1="170.18" y1="149.86" x2="172.72" y2="149.86" width="0.1524" layer="91"/>
<wire x1="172.72" y1="149.86" x2="210.82" y2="111.76" width="0.1524" layer="91"/>
<pinref part="JP10" gate="G$1" pin="1"/>
<wire x1="210.82" y1="111.76" x2="215.9" y2="111.76" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$41" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D5/PWM"/>
<pinref part="JP10" gate="G$1" pin="2"/>
<wire x1="170.18" y1="152.4" x2="172.72" y2="152.4" width="0.1524" layer="91"/>
<wire x1="172.72" y1="152.4" x2="215.9" y2="109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$42" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D4/CAN-RX/PWM"/>
<wire x1="170.18" y1="154.94" x2="172.72" y2="154.94" width="0.1524" layer="91"/>
<wire x1="172.72" y1="154.94" x2="213.36" y2="114.3" width="0.1524" layer="91"/>
<wire x1="213.36" y1="114.3" x2="213.36" y2="106.68" width="0.1524" layer="91"/>
<pinref part="JP10" gate="G$1" pin="3"/>
<wire x1="213.36" y1="106.68" x2="215.9" y2="106.68" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$43" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D3/CAN-TX/PWM"/>
<wire x1="170.18" y1="157.48" x2="172.72" y2="157.48" width="0.1524" layer="91"/>
<wire x1="172.72" y1="157.48" x2="210.82" y2="119.38" width="0.1524" layer="91"/>
<wire x1="210.82" y1="119.38" x2="210.82" y2="104.14" width="0.1524" layer="91"/>
<pinref part="JP10" gate="G$1" pin="4"/>
<wire x1="210.82" y1="104.14" x2="215.9" y2="104.14" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$44" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D2"/>
<wire x1="170.18" y1="160.02" x2="177.8" y2="160.02" width="0.1524" layer="91"/>
<wire x1="177.8" y1="160.02" x2="177.8" y2="154.94" width="0.1524" layer="91"/>
<wire x1="177.8" y1="154.94" x2="205.74" y2="127" width="0.1524" layer="91"/>
<pinref part="JP10" gate="G$1" pin="5"/>
<wire x1="205.74" y1="127" x2="205.74" y2="111.76" width="0.1524" layer="91"/>
<wire x1="205.74" y1="111.76" x2="215.9" y2="101.6" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$45" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D1/TX1/TOUCH"/>
<pinref part="JP10" gate="G$1" pin="6"/>
<wire x1="170.18" y1="162.56" x2="215.9" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$46" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D0/RX1/TOUCH"/>
<wire x1="170.18" y1="165.1" x2="228.6" y2="106.68" width="0.1524" layer="91"/>
<wire x1="228.6" y1="106.68" x2="228.6" y2="93.98" width="0.1524" layer="91"/>
<wire x1="228.6" y1="93.98" x2="215.9" y2="93.98" width="0.1524" layer="91"/>
<pinref part="JP5" gate="G$1" pin="1"/>
<wire x1="215.9" y1="93.98" x2="215.9" y2="91.44" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$47" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="A13/ADC0_DM3"/>
<wire x1="170.18" y1="71.12" x2="185.42" y2="71.12" width="0.1524" layer="91"/>
<wire x1="185.42" y1="71.12" x2="185.42" y2="86.36" width="0.1524" layer="91"/>
<pinref part="JP5" gate="G$1" pin="3"/>
<wire x1="185.42" y1="86.36" x2="215.9" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$48" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D33/PWM/TOUCH"/>
<pinref part="JP5" gate="G$1" pin="5"/>
<wire x1="170.18" y1="81.28" x2="215.9" y2="81.28" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$49" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D32/PWM/TOUCH"/>
<wire x1="170.18" y1="83.82" x2="208.28" y2="83.82" width="0.1524" layer="91"/>
<wire x1="208.28" y1="83.82" x2="208.28" y2="78.74" width="0.1524" layer="91"/>
<pinref part="JP5" gate="G$1" pin="6"/>
<wire x1="208.28" y1="78.74" x2="215.9" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$50" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D31/A20"/>
<wire x1="170.18" y1="86.36" x2="210.82" y2="86.36" width="0.1524" layer="91"/>
<wire x1="210.82" y1="86.36" x2="210.82" y2="71.12" width="0.1524" layer="91"/>
<pinref part="JP6" gate="G$1" pin="1"/>
<wire x1="210.82" y1="71.12" x2="215.9" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$51" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D30/A19/SDA1"/>
<wire x1="170.18" y1="88.9" x2="193.04" y2="88.9" width="0.1524" layer="91"/>
<wire x1="193.04" y1="88.9" x2="193.04" y2="68.58" width="0.1524" layer="91"/>
<pinref part="JP6" gate="G$1" pin="2"/>
<wire x1="193.04" y1="68.58" x2="215.9" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$52" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D29/A18/SCL1"/>
<wire x1="170.18" y1="91.44" x2="205.74" y2="91.44" width="0.1524" layer="91"/>
<wire x1="205.74" y1="91.44" x2="205.74" y2="66.04" width="0.1524" layer="91"/>
<pinref part="JP6" gate="G$1" pin="3"/>
<wire x1="205.74" y1="66.04" x2="215.9" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$53" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D28/A17"/>
<wire x1="170.18" y1="93.98" x2="203.2" y2="93.98" width="0.1524" layer="91"/>
<wire x1="203.2" y1="93.98" x2="203.2" y2="63.5" width="0.1524" layer="91"/>
<pinref part="JP6" gate="G$1" pin="4"/>
<wire x1="203.2" y1="63.5" x2="215.9" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$54" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D27/A16"/>
<wire x1="170.18" y1="96.52" x2="200.66" y2="96.52" width="0.1524" layer="91"/>
<wire x1="200.66" y1="96.52" x2="200.66" y2="60.96" width="0.1524" layer="91"/>
<pinref part="JP6" gate="G$1" pin="5"/>
<wire x1="200.66" y1="60.96" x2="215.9" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$55" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D26/A15"/>
<wire x1="170.18" y1="99.06" x2="198.12" y2="99.06" width="0.1524" layer="91"/>
<wire x1="198.12" y1="99.06" x2="198.12" y2="58.42" width="0.1524" layer="91"/>
<pinref part="JP6" gate="G$1" pin="6"/>
<wire x1="198.12" y1="58.42" x2="215.9" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$56" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D25/PWM/TOUCH"/>
<wire x1="170.18" y1="101.6" x2="187.96" y2="101.6" width="0.1524" layer="91"/>
<wire x1="187.96" y1="101.6" x2="187.96" y2="50.8" width="0.1524" layer="91"/>
<pinref part="JP9" gate="G$1" pin="1"/>
<wire x1="187.96" y1="50.8" x2="215.9" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$57" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D24"/>
<wire x1="170.18" y1="104.14" x2="213.36" y2="60.96" width="0.1524" layer="91"/>
<wire x1="213.36" y1="60.96" x2="213.36" y2="48.26" width="0.1524" layer="91"/>
<pinref part="JP9" gate="G$1" pin="2"/>
<wire x1="213.36" y1="48.26" x2="215.9" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$58" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="A12/ADC0_DP3"/>
<pinref part="JP9" gate="G$1" pin="4"/>
<wire x1="170.18" y1="73.66" x2="200.66" y2="43.18" width="0.1524" layer="91"/>
<wire x1="200.66" y1="43.18" x2="215.9" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$59" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D8/TX3"/>
<wire x1="170.18" y1="144.78" x2="233.68" y2="144.78" width="0.1524" layer="91"/>
<pinref part="JP11" gate="G$1" pin="1"/>
<wire x1="233.68" y1="144.78" x2="233.68" y2="106.68" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$60" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D16/A2/TOUCH"/>
<pinref part="JP11" gate="G$1" pin="2"/>
<wire x1="170.18" y1="124.46" x2="190.5" y2="104.14" width="0.1524" layer="91"/>
<wire x1="190.5" y1="104.14" x2="233.68" y2="104.14" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$61" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="A14/DAC"/>
<pinref part="JP9" gate="G$1" pin="5"/>
<wire x1="170.18" y1="68.58" x2="198.12" y2="40.64" width="0.1524" layer="91"/>
<wire x1="198.12" y1="40.64" x2="215.9" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$63" class="0">
<segment>
<pinref part="F1" gate="G$1" pin="1"/>
<wire x1="40.64" y1="154.94" x2="35.56" y2="154.94" width="0.1524" layer="91"/>
<wire x1="35.56" y1="154.94" x2="35.56" y2="165.1" width="0.1524" layer="91"/>
<wire x1="35.56" y1="165.1" x2="25.4" y2="165.1" width="0.1524" layer="91"/>
<pinref part="C3" gate="G$1" pin="+"/>
<wire x1="25.4" y1="165.1" x2="17.78" y2="165.1" width="0.1524" layer="91"/>
<wire x1="25.4" y1="165.1" x2="25.4" y2="132.08" width="0.1524" layer="91"/>
<junction x="25.4" y="165.1"/>
<pinref part="JP1" gate="G$1" pin="VCC"/>
<wire x1="25.4" y1="132.08" x2="17.78" y2="132.08" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
