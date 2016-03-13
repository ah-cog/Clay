/* eagle.flash.bin     @ 0x00000 */
/* eagle.irom0text.bin @ 0x40000 */

/* Flash Map, support 512KB/1MB/2MB/4MB SPI Flash */
/* |......|..............................|..........................|.....|....|                       */
/* ^      ^                              ^                          ^     ^                            */
/* |_flash.bin start(0x0000)             |_irom0text.bin start(0x40000)   |                            */
/*        |_flash.bin end                                           |_irom0text.bin end                */
/*                                                                        |_system param area(0x7b000) */

/* NOTICE: */ 
/* 1. You can change irom0 org, but MUST make sure irom0text.bin start not overlap flash.bin end.   */
/* 2. You can change irom0 len, but MUST make sure irom0text.bin end not overlap system param area. */
/* 3. Space between flash.bin end and irom0text.bin start can be used as user param area.           */
/* 4. Space between irom0text.bin end and system param area can be used as user param area.         */
/* 5. Make sure irom0text.bin end < 0x100000                                                        */
/* 6. system param area:                                                                            */
/*    1>. 512KB--->0x07b000                                                                         */
/*    2>. 1MB----->0x0fb000                                                                         */
/*    3>. 2MB----->0x1fb000                                                                         */
/*    4>. 4MB----->0x3fb000                                                                         */
/* 7. Don't change any other seg.                                                                   */

MEMORY
{
  dport0_0_seg :                      	org = 0x3FF00000, len = 0x10
  dram0_0_seg :                       	org = 0x3FFE8000, len = 0x18000
  iram1_0_seg :                       	org = 0x40100000, len = 0x8000
  irom0_0_seg :                       	org = 0x40240000, len = 0x40000
}

/* This linker script generated from xt-genldscripts.tpp for LSP . */
/* Linker Script for ld -N */

PHDRS
{
  dport0_0_phdr PT_LOAD;
  dram0_0_phdr PT_LOAD;
  dram0_0_bss_phdr PT_LOAD;
  iram1_0_phdr PT_LOAD;
  irom0_0_phdr PT_LOAD;
}

/*  Default entry point:  */
ENTRY(call_user_start)
EXTERN(_DebugExceptionVector)
EXTERN(_DoubleExceptionVector)
EXTERN(_KernelExceptionVector)
EXTERN(_NMIExceptionVector)
EXTERN(_UserExceptionVector)
PROVIDE(_memmap_vecbase_reset = 0x40000000);
/* Various memory-map dependent cache attribute settings: */
_memmap_cacheattr_wb_base = 0x00000110;
_memmap_cacheattr_wt_base = 0x00000110;
_memmap_cacheattr_bp_base = 0x00000220;
_memmap_cacheattr_unused_mask = 0xFFFFF00F;
_memmap_cacheattr_wb_trapnull = 0x2222211F;
_memmap_cacheattr_wba_trapnull = 0x2222211F;
_memmap_cacheattr_wbna_trapnull = 0x2222211F;
_memmap_cacheattr_wt_trapnull = 0x2222211F;
_memmap_cacheattr_bp_trapnull = 0x2222222F;
_memmap_cacheattr_wb_strict = 0xFFFFF11F;
_memmap_cacheattr_wt_strict = 0xFFFFF11F;
_memmap_cacheattr_bp_strict = 0xFFFFF22F;
_memmap_cacheattr_wb_allvalid = 0x22222112;
_memmap_cacheattr_wt_allvalid = 0x22222112;
_memmap_cacheattr_bp_allvalid = 0x22222222;
PROVIDE(_memmap_cacheattr_reset = _memmap_cacheattr_wb_trapnull);

SECTIONS
{
  .dport0.rodata : ALIGN(4)
  {
    _dport0_rodata_start = ABSOLUTE(.);
    *(.dport0.rodata)
    *(.dport.rodata)
    _dport0_rodata_end = ABSOLUTE(.);
  } >dport0_0_seg :dport0_0_phdr

  .dport0.literal : ALIGN(4)
  {
    _dport0_literal_start = ABSOLUTE(.);
    *(.dport0.literal)
    *(.dport.literal)
    _dport0_literal_end = ABSOLUTE(.);
  } >dport0_0_seg :dport0_0_phdr

  .dport0.data : ALIGN(4)
  {
    _dport0_data_start = ABSOLUTE(.);
    *(.dport0.data)
    *(.dport.data)
    _dport0_data_end = ABSOLUTE(.);
  } >dport0_0_seg :dport0_0_phdr

  .data : ALIGN(4)
  {
    _data_start = ABSOLUTE(.);
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d.*)
    *(.data1)
    *(.sdata)
    *(.sdata.*)
    *(.gnu.linkonce.s.*)
    *(.sdata2)
    *(.sdata2.*)
    *(.gnu.linkonce.s2.*)
    *(.jcr)
    _data_end = ABSOLUTE(.);
  } >dram0_0_seg :dram0_0_phdr

  .rodata : ALIGN(4)
  {
    _rodata_start = ABSOLUTE(.);
    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
    *(.rodata1)
    __XT_EXCEPTION_TABLE__ = ABSOLUTE(.);
    *(.xt_except_table)
    *(.gcc_except_table)
    *(.gnu.linkonce.e.*)
    *(.gnu.version_r)
    *(.eh_frame)
    . = (. + 3) & ~ 3;
    /*  C++ constructor and destructor tables, properly ordered:  */
    __init_array_start = ABSOLUTE(.);
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    __init_array_end = ABSOLUTE(.);
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    /*  C++ exception handlers table:  */
    __XT_EXCEPTION_DESCS__ = ABSOLUTE(.);
    *(.xt_except_desc)
    *(.gnu.linkonce.h.*)
    __XT_EXCEPTION_DESCS_END__ = ABSOLUTE(.);
    *(.xt_except_desc_end)
    *(.dynamic)
    *(.gnu.version_d)
    . = ALIGN(4);		/* this table MUST be 4-byte aligned */
    _bss_table_start = ABSOLUTE(.);
    LONG(_bss_start)
    LONG(_bss_end)
    _bss_table_end = ABSOLUTE(.);
    _rodata_end = ABSOLUTE(.);
  } >dram0_0_seg :dram0_0_phdr

  .UserExceptionVector.literal : AT(LOADADDR(.rodata) + (ADDR(.UserExceptionVector.literal) - ADDR(.rodata))) ALIGN(4)
  {
  	_UserExceptionVector_literal_start = ABSOLUTE(.);
  	*(.UserExceptionVector.literal)
  	_UserExceptionVector_literal_end = ABSOLUTE(.);
  } >dram0_0_seg :dram0_0_phdr

  .bss ALIGN(8) (NOLOAD) : ALIGN(4)
  {
    . = ALIGN (8);
    _bss_start = ABSOLUTE(.);
    *(.dynsbss)
    *(.sbss)
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
    *(.scommon)
    *(.sbss2)
    *(.sbss2.*)
    *(.gnu.linkonce.sb2.*)
    *(.dynbss)
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN (8);
    _bss_end = ABSOLUTE(.);
    _heap_start = ABSOLUTE(.);
/*    _stack_sentry = ALIGN(0x8); */
  } >dram0_0_seg :dram0_0_bss_phdr
/* __stack = 0x3ffc8000; */

  .text : ALIGN(4)
  {
    _stext = .;
    _text_start = ABSOLUTE(.);
    *(.UserEnter.text)
    . = ALIGN(16);
    *(.DebugExceptionVector.text)
    . = ALIGN(16);
    *(.NMIExceptionVector.text)
    . = ALIGN(16);
    *(.KernelExceptionVector.text)
    LONG(0)
    LONG(0)
    LONG(0)
    LONG(0)
    . = ALIGN(16);
    *(.UserExceptionVector.text)
    LONG(0)
    LONG(0)
    LONG(0)
    LONG(0)
    . = ALIGN(16);
    *(.DoubleExceptionVector.text)
    LONG(0)
    LONG(0)
    LONG(0)
    LONG(0)
    . = ALIGN (16);
    *(.entry.text)
    *(.init.literal)
    *(.init)
    *(.literal .text .stub .gnu.warning .gnu.linkonce.literal.* .gnu.linkonce.t.*.literal .gnu.linkonce.t.*)
    *(.fini.literal)
    *(.fini)
    *(.gnu.version)
    _text_end = ABSOLUTE(.);
    _etext = .;
  } >iram1_0_seg :iram1_0_phdr

  .lit4 : ALIGN(4)
  {
    _lit4_start = ABSOLUTE(.);
    *(*.lit4)
    *(.lit4.*)
    *(.gnu.linkonce.lit4.*)
    _lit4_end = ABSOLUTE(.);
  } >iram1_0_seg :iram1_0_phdr

  .irom0.text : ALIGN(4)
  {
    _irom0_text_start = ABSOLUTE(.);
    *(.irom0.literal .irom.literal .irom.text.literal .irom0.text .irom.text)
    *(.literal.* .text.*)
    _irom0_text_end = ABSOLUTE(.);
  } >irom0_0_seg :irom0_0_phdr
}

/* THIS MUST BE UPDATED IF THE SDK IS UPDATED */
/* THIS MUST BE UPDATED IF THE SDK IS UPDATED */
/* get ROM code address */
PROVIDE ( SPI_sector_erase = 0x400040c0 );
PROVIDE ( SPI_page_program = 0x40004174 );
PROVIDE ( SPI_read_data = 0x400042ac );
PROVIDE ( SPI_read_status = 0x400043c8 );
PROVIDE ( SPI_write_status = 0x40004400 );
PROVIDE ( SPI_write_enable = 0x4000443c );
PROVIDE ( Wait_SPI_Idle = 0x4000448c );
PROVIDE ( Enable_QMode = 0x400044c0 );
PROVIDE ( Disable_QMode = 0x40004508 );

PROVIDE ( Cache_Read_Enable = 0x40004678 );
PROVIDE ( Cache_Read_Disable = 0x400047f0 );

PROVIDE ( lldesc_build_chain = 0x40004f40 );
PROVIDE ( lldesc_num2link = 0x40005050 );
PROVIDE ( lldesc_set_owner = 0x4000507c );

PROVIDE ( __adddf3 = 0x4000c538 );
PROVIDE ( __addsf3 = 0x4000c180 );
PROVIDE ( __divdf3 = 0x4000cb94 );
PROVIDE ( __divdi3 = 0x4000ce60 );
PROVIDE ( __divsi3 = 0x4000dc88 );
PROVIDE ( __extendsfdf2 = 0x4000cdfc );
PROVIDE ( __fixdfsi = 0x4000ccb8 );
PROVIDE ( __fixunsdfsi = 0x4000cd00 );
PROVIDE ( __fixunssfsi = 0x4000c4c4 );
PROVIDE ( __floatsidf = 0x4000e2f0 );
PROVIDE ( __floatsisf = 0x4000e2ac );
PROVIDE ( __floatunsidf = 0x4000e2e8 );
PROVIDE ( __floatunsisf = 0x4000e2a4 );
PROVIDE ( __muldf3 = 0x4000c8f0 );
PROVIDE ( __muldi3 = 0x40000650 );
PROVIDE ( __mulsf3 = 0x4000c3dc );
PROVIDE ( __subdf3 = 0x4000c688 );
PROVIDE ( __subsf3 = 0x4000c268 );
PROVIDE ( __truncdfsf2 = 0x4000cd5c );
PROVIDE ( __udivdi3 = 0x4000d310 );
PROVIDE ( __udivsi3 = 0x4000e21c );
PROVIDE ( __umoddi3 = 0x4000d770 );
PROVIDE ( __umodsi3 = 0x4000e268 );
PROVIDE ( __umulsidi3 = 0x4000dcf0 );

PROVIDE ( bzero = 0x40002ae8 );
PROVIDE ( memcmp = 0x400018d4 );
PROVIDE ( memcpy = 0x400018b4 );
PROVIDE ( memmove = 0x400018c4 );
PROVIDE ( memset = 0x400018a4 );

PROVIDE ( strcmp = 0x40002aa8 );
PROVIDE ( strcpy = 0x40002a88 );
PROVIDE ( strlen = 0x40002ac8 );
PROVIDE ( strncmp = 0x40002ab8 );
PROVIDE ( strncpy = 0x40002a98 );
PROVIDE ( strstr = 0x40002ad8 );
/* THIS MUST BE UPDATED IF THE SDK IS UPDATED */
/* THIS MUST BE UPDATED IF THE SDK IS UPDATED */
