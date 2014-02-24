/***************************************************************************
* $Id$
*
* Author: Yaping Wang, March 2013
****************************************************************************/

#include "StIstRawHit.h"
#include "StIstRawHitCollection.h"
#include <cmath>
#include <iostream>


StIstRawHitCollection::StIstRawHitCollection( unsigned char ladder ) : StObject(), mLadder(ladder), mRawHitVec(), mRawHitElecIdVec(kIstNumElecIds)
{
}


/** Free memory and clear the vector */
StIstRawHitCollection::~StIstRawHitCollection()
{
   while (!mRawHitVec.empty()) delete mRawHitVec.back(), mRawHitVec.pop_back();

   mRawHitElecIdVec.clear();
};

//sort internal vector by raw hit geometry ID
void StIstRawHitCollection::sortByGeoId()
{
   std::sort( mRawHitVec.begin(), mRawHitVec.end(), &StIstRawHitCollection::rawHitIdLessThan );
};

bool StIstRawHitCollection::rawHitIdLessThan( const StIstRawHit *h1, const StIstRawHit *h2 )
{
   return (h1->getGeoId() < h2->getGeoId());
};

vector<StIstRawHit *> &StIstRawHitCollection::getRawHitVec()
{
   return mRawHitVec;
};

const vector<StIstRawHit *> &StIstRawHitCollection::getRawHitVec() const
{
   return mRawHitVec;
};

size_t StIstRawHitCollection::getNumRawHits() const
{
   return mRawHitVec.size();
};

void StIstRawHitCollection::setLadder( unsigned char ladder )
{
   mLadder = ladder;
};

unsigned char StIstRawHitCollection::getLadder() const
{
   return mLadder;
};

void StIstRawHitCollection::Clear( Option_t *opt )
{
   while (!mRawHitVec.empty()) delete mRawHitVec.back(), mRawHitVec.pop_back();

   //clear the vector for alternate lookups
   for (unsigned int i = 0; i < mRawHitElecIdVec.size(); i++)
      mRawHitElecIdVec[i] = 0;
};

StIstRawHit *StIstRawHitCollection::getRawHit( int elecId )
{
   StIstRawHit *&rawHitPtr = mRawHitElecIdVec[elecId];
   if ( !rawHitPtr ) {
      rawHitPtr = new StIstRawHit();
      mRawHitVec.push_back( rawHitPtr );
   }
   return rawHitPtr;
};

ClassImp(StIstRawHitCollection);


/***************************************************************************
* $Log$
* Revision 1.13  2014/02/24 14:49:23  ypwang
* update Clear( Option_t *opt ) to delete StIstRawHit objects from mRawHitVec
*
* Revision 1.12  2014/02/24 14:24:40  ypwang
* get rid of StIstRawHitCollection::removeFlagged()
*
* Revision 1.11  2014/02/20 02:31:22  smirnovd
* Minor style corrections
*
* Revision 1.10  2014/02/20 02:31:00  smirnovd
* Use constructor list to initialize vectors of pointers and arrays
*
* Revision 1.9  2014/02/20 02:30:45  smirnovd
* Simplified the destructor
*
* Revision 1.8  2014/02/20 02:30:26  smirnovd
* Remove one level of indentation
*
* Revision 1.7  2014/02/20 02:29:55  smirnovd
* Reverse if statement to remove extra indentation
*
* Revision 1.6  2014/02/15 23:32:57  ypwang
* update destructor and Clear() function
*
* Revision 1.5  2014/02/14 14:51:06  ypwang
* update Clear() function, and call Clear() function in deconstructor
*
* Revision 1.4  2014/02/13 02:35:49  smirnovd
* Moved CVS log to the bottom of the file
*
* Revision 1.3  2014/02/03 16:12:20  ypwang
* updating scripts
*
****************************************************************************
* StIstRawHitCollection.cxx,v 1.0
* Revision 1.0 2013/11/04 15:05:30 Yaping
* Initial version
****************************************************************************/
