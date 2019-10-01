/*
-- ----------------------------------------------------------------------------
--
--     SCCS ID : @(#)  setconf.inc 1.7 92/06/15 10:12:13
--
--     Object Name : setconf.inc
--     Revision    : 1.7
--
--     (c) Copyright INMOS Limited.
--     All Rights Reserved.
--
--     DESCRIPTION
--         Include file of INMOS 'C' configurer defaults.
--
--     NOTES
--         None.
--
--     HISTORY
--         1-Jun-1990    Antony King    Created file.
--
-- ----------------------------------------------------------------------------
*/

/*{{{  Definitions selector */
val __hardware__ 1;
val __HARDWARE__ __hardware__;

val __software__ 1;
val __SOFTWARE__ __software__;
/*}}}*/

/*{{{  Constant definitions */
/*{{{  Boolean constants */
if __software__ || __hardware__
  {
    /*{{{   */
    val false 0;
    val true  1;
    /*}}}*/
  }

if __SOFTWARE__ || __HARDWARE__
  {
    /*{{{   */
    val FALSE 0;
    val TRUE  1;
    /*}}}*/
  }
/*}}}*/

/*{{{  Priority constants */
if __software__
  {
    /*{{{   */
    val high 0;
    val low  1;
    /*}}}*/
  }

if __SOFTWARE__
  {
    /*{{{   */
    val HIGH 0;
    val LOW  1;
    /*}}}*/
  }
/*}}}*/

/*{{{  Routing constants */
if __software__
  {
    /*{{{   */
    val min_cost      1;
    val max_cost      1000000;
    val default_cost  1000;
    val infinite_cost 1000001;
    
    val zero_tolerance    0;
    val default_tolerance 1;
    val max_tolerance     1000000;
    
    val muxer_order  -10000;
    val router_order -20000;
    /*}}}*/
  }

if __SOFTWARE__
  {
    /*{{{   */
    val MIN_COST      1;
    val MAX_COST      1000000;
    val DEFAULT_COST  1000;
    val INFINITE_COST 1000001;
    
    val ZERO_TOLERANCE    0;
    val DEFAULT_TOLERANCE 1;
    val MAX_TOLERANCE     1000000;
    
    val MUXER_ORDER  -10000;
    val ROUTER_ORDER -20000;
    /*}}}*/
  }
/*}}}*/
/*}}}*/

/*{{{  Hardware definitions */
if __hardware__
  {
    /*{{{   */
    define node (element = "processor") processor;
    
    define node (element = "processor", type = "T805") t805;
    define node (element = "processor", type = "T801") t801;
    define node (element = "processor", type = "T800") t800;
    define node (element = "processor", type = "T426") t426;
    define node (element = "processor", type = "T425") t425;
    define node (element = "processor", type = "T414") t414;
    define node (element = "processor", type = "T400") t400;
    define node (element = "processor", type = "T225") t225;
    define node (element = "processor", type = "T222") t222;
    define node (element = "processor", type = "T212") t212;
    define node (element = "processor", type = "M212") m212;
    /*}}}*/
  }

if __HARDWARE__
  {
    /*{{{   */
    define node (element = "processor") PROCESSOR;
    
    define node (element = "processor", type = "T805") T805;
    define node (element = "processor", type = "T801") T801;
    define node (element = "processor", type = "T800") T800;
    define node (element = "processor", type = "T426") T426;
    define node (element = "processor", type = "T425") T425;
    define node (element = "processor", type = "T414") T414;
    define node (element = "processor", type = "T400") T400;
    define node (element = "processor", type = "T225") T225;
    define node (element = "processor", type = "T222") T222;
    define node (element = "processor", type = "T212") T212;
    define node (element = "processor", type = "M212") M212;
    /*}}}*/
  }
/*}}}*/

/*{{{  Software definitions */
if __software__
  {
    /*{{{   */
    define node (element = "process") process;
    
    define node (element = "process", priority = high) highprocess;
    define node (element = "process", priority = low) lowprocess;
    /*}}}*/
  }

if __SOFTWARE__
  {
    /*{{{   */
    define node (element = "process") PROCESS;
    
    define node (element = "process", priority = HIGH) HIGHPROCESS;
    define node (element = "process", priority = LOW) LOWPROCESS;
    /*}}}*/
  }
/*}}}*/

/*{{{  Network to host link */
if __hardware__ || __HARDWARE__
  {
    /*{{{   */
    edge host;
    /*}}}*/
  }
/*}}}*/
