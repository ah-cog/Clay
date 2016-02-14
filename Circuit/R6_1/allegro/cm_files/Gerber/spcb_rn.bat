set cba_name=c6r2
mkdir %cba_name%_out
copy TOP.art "%cba_name%_out/%cba_name%.gtl"
copy GND.art "%cba_name%_out/%cba_name%.g2l"
copy PWR.art "%cba_name%_out/%cba_name%.g3l"
copy BOTTOM.art "%cba_name%_out/%cba_name%.gbl"
copy SILK_TOP.art "%cba_name%_out/%cba_name%.gto"
copy SILK_BOTTOM.art "%cba_name%_out/%cba_name%.gbo"
copy SOLDERMASK_TOP.art "%cba_name%_out/%cba_name%.gts"
copy SOLDERMASK_BOTTOM.art "%cba_name%_out/%cba_name%.gbs"
copy OUTLINE.art "%cba_name%_out/%cba_name%.gml"
copy PASTE_TOP.art "%cba_name%_out/%cba_name%.gtp"
copy *.drl "%cba_name%_out/%cba_name%.txt"