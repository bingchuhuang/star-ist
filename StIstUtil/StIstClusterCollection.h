#ifndef StIstClusterCollection_hh
#define StIstClusterCollection_hh

#include "StObject.h"
#include "StIstCluster.h"


/**
 * A collection of StIstCluster objects which is basically a wrapper for
 * a clusters vector. One instance corresponds to one ladder.
 *
 * \author Yaping Wang
 * \date March 2013
 */
class StIstClusterCollection : public StObject
{
public:

   StIstClusterCollection(int ladder = 0);
   ~StIstClusterCollection();

   vector<StIstCluster *> &getClusterVec();
   const vector<StIstCluster *> &getClusterVec() const;

   //size of internal vector
   size_t getNumClusters() const;

   //modify/access the ladder
   unsigned char getLadder() const;
   void setLadder( int ladder );

   void Clear( Option_t *opt = "" );
   virtual void Print(Option_t *opt = "") const;

protected:

   unsigned char mLadder;
   std::vector<StIstCluster *> mClusterVec;

   ClassDef(StIstClusterCollection, 1);
};

#endif


/***************************************************************************
*
* $Log: StIstClusterCollection.h,v $
* Revision 1.8  2014/11/18 23:11:36  smirnovd
* [Minor] Coding style clean-up. Removed unconstructive comments
*
* Revision 1.7  2014/11/18 23:08:38  smirnovd
* Moved CVS log to the end of file and updated doxygen-style comments
*
* Revision 1.6  2014/09/09 08:23:46  ypwang
* all unsgined char was updated to int type as Victor P. suggested
*
* Revision 1.5  2014/09/08 19:06:57  smirnovd
* Added Print() methods to print out properties of StIstCluster and StIstRawHit objects and their respective collections
*
* Revision 1.4  2014/02/13 02:35:49  smirnovd
* Moved CVS log to the bottom of the file
*
* Revision 1.3  2014/02/03 16:12:20  ypwang
* updating scripts
*
*
****************************************************************************
* StIstClusterCollection.h,v 1.0
* Revision 1.0 2013/11/04 15:15:30 Yaping
* Initial version
****************************************************************************/
