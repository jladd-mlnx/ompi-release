/* ---------------------------------------------------------------- */
/* (C)Copyright IBM Corp.  2007, 2008                               */
/* ---------------------------------------------------------------- */
/**
 * \file ad_bg_pset.h
 * \brief ???
 */

/* File: ad_bg_pset.h
 *
 * Defines two structures that keep BG/L PSET specific information and their public interfaces:
 * 	. ADIOI_BG_ProcInfo_t object keeps specific information to each process
 * 	. ADIOI_BG_ConfInfo_t object keeps general information for the whole communicator, only kept
 *	  on process 0.
 */

#ifndef AD_BG_PSET_H_
#define AD_BG_PSET_H_

/* Keeps specific information to each process, will be exchanged among processes */
typedef struct {
   int ioNodeIndex; /* similar to psetNum on BGL/BGP */
   int rank; /* my rank */
/*   int myCoords[5]; */
   int bridgeRank; /* my bridge node (or proxy) rank */
   unsigned char coreID;
   unsigned char threadID; /* unlikely to be useful but better than just padding */
   unsigned char __cpad[2];
   int myIOSize;  /* number of ranks sharing my bridge/IO
      node, i.e. psetsize*/
   int iamBridge; /* am *I* the bridge rank? */
   int __ipad[2];
} ADIOI_BG_ProcInfo_t __attribute__((aligned(16)));

/* Keeps general information for the whole communicator, only on process 0 */
typedef struct {
   int ioMinSize; /* Smallest number of ranks shareing 1 bridge node */
   int ioMaxSize; /* Largest number of ranks sharing 1 bridge node */
   /* ioMaxSize will be the "psetsize" */
   int nAggrs;
   int numBridgeRanks;
   /*int virtualPsetSize; ppn * pset size */
   int nProcs;
   int cpuIDsize; /* num ppn */
   float aggRatio;

} ADIOI_BG_ConfInfo_t __attribute__((aligned(16)));


#undef MIN
#define MIN(a,b) ((a<b ? a : b))


/* Default is to choose 8 aggregator nodes in each 32 CN pset.
   Also defines default ratio of aggregator nodes in each a pset.
   For Virtual Node Mode, the ratio is 8/64 */
#define ADIOI_BG_NAGG_PSET_MIN  1
#define ADIOI_BG_NAGG_PSET_DFLT 8
#define ADIOI_BG_PSET_SIZE_DFLT 32


/* public funcs for ADIOI_BG_ProcInfo_t objects */
    ADIOI_BG_ProcInfo_t * ADIOI_BG_ProcInfo_new();
    ADIOI_BG_ProcInfo_t * ADIOI_BG_ProcInfo_new_n( int n );
    void ADIOI_BG_ProcInfo_free( ADIOI_BG_ProcInfo_t *info );


/* public funcs for ADIOI_BG_ConfInfo_t objects */
    ADIOI_BG_ConfInfo_t * ADIOI_BG_ConfInfo_new ();
    void ADIOI_BG_ConfInfo_free( ADIOI_BG_ConfInfo_t *info );


/* public funcs for a pair of ADIOI_BG_ConfInfo_t and ADIOI_BG_ProcInfo_t objects */
    void ADIOI_BG_persInfo_init( ADIOI_BG_ConfInfo_t *conf,
				  ADIOI_BG_ProcInfo_t *proc,
				  int s, int r, int n_aggrs, MPI_Comm comm);
    void ADIOI_BG_persInfo_free( ADIOI_BG_ConfInfo_t *conf,
				  ADIOI_BG_ProcInfo_t *proc );


#endif  /* AD_BG_PSET_H_ */
