/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_OS_ILLUMINANCEMAP_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ILLUMINANCEMAP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_IlluminanceMapFields
 *  \brief Enumeration of OS:IlluminanceMap's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_IlluminanceMapFields, )
#else
class OS_IlluminanceMapFields: public ::EnumBase<OS_IlluminanceMapFields> {
 public: 
  enum domain 
  {
Handle, Name, SpaceName, OriginXCoordinate, OriginYCoordinate, OriginZCoordinate, PsiRotationAroundXAxis, ThetaRotationAroundYAxis, PhiRotationAroundZAxis, XLength, NumberofXGridPoints, YLength, NumberofYGridPoints,   };
  OS_IlluminanceMapFields()
   : EnumBase<OS_IlluminanceMapFields>(Handle) {} 
  OS_IlluminanceMapFields(const std::string &t_name) 
   : EnumBase<OS_IlluminanceMapFields>(t_name) {} 
  OS_IlluminanceMapFields(int t_value) 
   : EnumBase<OS_IlluminanceMapFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_IlluminanceMapFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_IlluminanceMapFields>::value()); }
   private:
    friend class EnumBase<OS_IlluminanceMapFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ OS_IlluminanceMapFields::Handle, "Handle", "Handle"},
{ OS_IlluminanceMapFields::Name, "Name", "Name"},
{ OS_IlluminanceMapFields::SpaceName, "SpaceName", "Space Name"},
{ OS_IlluminanceMapFields::OriginXCoordinate, "OriginXCoordinate", "Origin X-Coordinate"},
{ OS_IlluminanceMapFields::OriginYCoordinate, "OriginYCoordinate", "Origin Y-Coordinate"},
{ OS_IlluminanceMapFields::OriginZCoordinate, "OriginZCoordinate", "Origin Z-Coordinate"},
{ OS_IlluminanceMapFields::PsiRotationAroundXAxis, "PsiRotationAroundXAxis", "Psi Rotation Around X-Axis"},
{ OS_IlluminanceMapFields::ThetaRotationAroundYAxis, "ThetaRotationAroundYAxis", "Theta Rotation Around Y-Axis"},
{ OS_IlluminanceMapFields::PhiRotationAroundZAxis, "PhiRotationAroundZAxis", "Phi Rotation Around Z-Axis"},
{ OS_IlluminanceMapFields::XLength, "XLength", "X Length"},
{ OS_IlluminanceMapFields::NumberofXGridPoints, "NumberofXGridPoints", "Number of X Grid Points"},
{ OS_IlluminanceMapFields::YLength, "YLength", "Y Length"},
{ OS_IlluminanceMapFields::NumberofYGridPoints, "NumberofYGridPoints", "Number of Y Grid Points"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const OS_IlluminanceMapFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_IlluminanceMapFields> OptionalOS_IlluminanceMapFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ILLUMINANCEMAP_FIELDENUMS_HXX
