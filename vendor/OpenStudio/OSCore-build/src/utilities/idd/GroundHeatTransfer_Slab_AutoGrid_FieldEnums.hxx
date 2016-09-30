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

#ifndef UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_AUTOGRID_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_AUTOGRID_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatTransfer_Slab_AutoGridFields
 *  \brief Enumeration of GroundHeatTransfer:Slab:AutoGrid's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatTransfer_Slab_AutoGridFields, )
#else
class GroundHeatTransfer_Slab_AutoGridFields: public ::EnumBase<GroundHeatTransfer_Slab_AutoGridFields> {
 public: 
  enum domain 
  {
SLABX_Xdimensionofthebuildingslab, SLABY_Ydimensionofthebuildingslab, SLABDEPTH_Thicknessofslabongrade, CLEARANCE_Distancefromedgeofslabtodomainedge, ZCLEARANCE_Distancefrombottomofslabtodomainbottom,   };
  GroundHeatTransfer_Slab_AutoGridFields()
   : EnumBase<GroundHeatTransfer_Slab_AutoGridFields>(SLABX_Xdimensionofthebuildingslab) {} 
  GroundHeatTransfer_Slab_AutoGridFields(const std::string &t_name) 
   : EnumBase<GroundHeatTransfer_Slab_AutoGridFields>(t_name) {} 
  GroundHeatTransfer_Slab_AutoGridFields(int t_value) 
   : EnumBase<GroundHeatTransfer_Slab_AutoGridFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatTransfer_Slab_AutoGridFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatTransfer_Slab_AutoGridFields>::value()); }
   private:
    friend class EnumBase<GroundHeatTransfer_Slab_AutoGridFields>;
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
{ GroundHeatTransfer_Slab_AutoGridFields::SLABX_Xdimensionofthebuildingslab, "SLABX_Xdimensionofthebuildingslab", "SLABX: X dimension of the building slab"},
{ GroundHeatTransfer_Slab_AutoGridFields::SLABY_Ydimensionofthebuildingslab, "SLABY_Ydimensionofthebuildingslab", "SLABY: Y dimension of the building slab"},
{ GroundHeatTransfer_Slab_AutoGridFields::SLABDEPTH_Thicknessofslabongrade, "SLABDEPTH_Thicknessofslabongrade", "SLABDEPTH: Thickness of slab on grade"},
{ GroundHeatTransfer_Slab_AutoGridFields::CLEARANCE_Distancefromedgeofslabtodomainedge, "CLEARANCE_Distancefromedgeofslabtodomainedge", "CLEARANCE: Distance from edge of slab to domain edge"},
{ GroundHeatTransfer_Slab_AutoGridFields::ZCLEARANCE_Distancefrombottomofslabtodomainbottom, "ZCLEARANCE_Distancefrombottomofslabtodomainbottom", "ZCLEARANCE: Distance from bottom of slab to domain bottom"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatTransfer_Slab_AutoGridFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatTransfer_Slab_AutoGridFields> OptionalGroundHeatTransfer_Slab_AutoGridFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_AUTOGRID_FIELDENUMS_HXX
