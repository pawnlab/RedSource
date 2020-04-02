
#ifndef _MImage
#define _MImage
//
//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc., and/or its licensors.  All 
// rights reserved.
// 
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors,  which is protected by U.S. and Canadian federal copyright law 
// and by international treaties.
// 
// The Data may not be disclosed or distributed to third parties or be 
// copied or duplicated, in whole or in part, without the prior written 
// consent of Autodesk.
// 
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the following 
// disclaimer, must be included in all copies of the Software, in whole 
// or in part, and all derivative works of the Software, unless such copies 
// or derivative works are solely in the form of machine-executable object 
// code generated by a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, 
// OR ARISING FROM A COURSE OF DEALING, USAGE, OR TRADE PRACTICE. IN NO 
// EVENT WILL AUTODESK AND/OR ITS LICENSORS BE LIABLE FOR ANY LOST 
// REVENUES, DATA, OR PROFITS, OR SPECIAL, DIRECT, INDIRECT, OR 
// CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS LICENSORS HAS 
// BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES. 
// ==========================================================================
//+
//
// CLASS:    MImage
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MImage)
//
// MImage is a class which provides access to some of Maya's image manipulation
// functionality.
//
// MImage provides methods for loading and resizing image files in any 
// Maya-supported format, including but not limited to IFF, SGI, Softimage, 
// TIFF, Alias PIX, GIF, RLA, JPEG, EPS.
// 
// MImage stores the image as an uncompressed array of pixels, that can be read
// and manipulate directly. That format is either RGBA (depth=4), RGB (depth=3),
// or Luminance (depth=1).
//
// (NOTE: At the moment, all files are directly converted to RGBA regardless
// of their original format. This restriction might get lifted in the future if
// there is enough interest.)
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MObject.h>
#include <maya/MString.h>
#include <maya/MTypes.h>

// *****************************************************************************

// CLASS DECLARATION (MImage)

/// Image manipulation
/**
This class provides methods for reading file images stored on disk.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

#define kIffStringDefault MString("iff")

class OPENMAYA_EXPORT MImage  
{
public:
	// Possible source or target filter formats.
	///
	enum MImageFilterFormat {
		///
		kNoFormat,
		///
		kHeightFieldBumpFormat,
		///
		kNormalMapBumpFormat,
		///	
		kUnknownFormat
	};

	// Possible source or target pixel formats.
	///
	enum MPixelType {
		///
		kUnknown,
		///
		kByte,
		///
		kFloat
	};

	///
					MImage();
	///
					~MImage();
	///
					MStatus create(unsigned int width, unsigned int height, unsigned int channels = 4, MPixelType type = kByte);
	///
					MStatus readFromFile(MString pathname, MPixelType type = kByte);
	///
					MStatus readFromTextureNode(const MObject& fileTextureObject, MPixelType type = kByte);
	///
					MStatus getSize(unsigned int &width, unsigned int &height) const;
	///
					MPixelType pixelType() const;
	///
					unsigned char* pixels() const;
	///
					float* floatPixels() const;
	///
					void setPixels(unsigned char* pixels, unsigned int width, unsigned int height);
	///
					void setFloatPixels(float* pixels, unsigned int width, unsigned int height, unsigned int channels = 4);
	///
					unsigned int depth();
    ///
					MStatus getDepthMapSize( unsigned int &width, unsigned int &height ) const;
    ///
					MStatus setDepthMap(float *depth, unsigned width, unsigned height );
	///				
					float *depthMap( MStatus *ReturnStatus = NULL ) const; 
	///
					MStatus readDepthMap(MString pathname); 
	///
					MStatus resize(int width, int height, bool preserveAspectRatio = true);
	///
					static bool filterExists(MImageFilterFormat sourceFormat, MImageFilterFormat targetFormat);
	///
					MStatus filter(MImageFilterFormat sourceFormat, MImageFilterFormat targetFormat, 
						double scale = 1.0, double offset = 0.0);
	///  
					MStatus writeToFile(MString pathname, MString outputFormat = kIffStringDefault );
	/// 				
					MStatus writeToFileWithDepth(MString pathname, MString outputFormat = kIffStringDefault, bool writeDepth = false );
	///
					MStatus release();
	///
					void verticalFlip();
	///
					void setRGBA(bool rgbaFormat);
	///				   
					bool haveDepth() const;
	///
					MStatus convertPixelFormat( MPixelType type, double scale = 1.0, double offset = 0.0);
	
protected:
	//
	MStatus			readFromFileInternalFixed(const MString & pathname, MPixelType pixelType, void* exposureControl = NULL);
	MStatus			readFromFileInternalFloat(const MString & pathname, MPixelType pixelType, void* exposureControl = NULL);
	MStatus			readFromFileInternal(const MString & pathname, MPixelType pixelType, void* exposureControl = NULL);

private:
	static const char *className();
	
	void set( void * );
	void setFloat( void * );

	
	void *_pPixelMap;
	void *_pFloatMap;
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MImage */
