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

#ifndef UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_MANUALGRID_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_MANUALGRID_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatTransfer_Slab_ManualGridFields
 *  \brief Enumeration of GroundHeatTransfer:Slab:ManualGrid's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatTransfer_Slab_ManualGridFields, )
#else
class GroundHeatTransfer_Slab_ManualGridFields: public ::EnumBase<GroundHeatTransfer_Slab_ManualGridFields> {
 public: 
  enum domain 
  {
NX_NumberofcellsintheXdirection, NY_NumberofcellsintheYdirection, NZ_NumberofcellsintheZdirection, IBOX_Xdirectioncellindicatorofslabedge, JBOX_Ydirectioncellindicatorofslabedge,   };
  GroundHeatTransfer_Slab_ManualGridFields()
   : EnumBase<GroundHeatTransfer_Slab_ManualGridFields>(NX_NumberofcellsintheXdirection) {} 
  GroundHeatTransfer_Slab_ManualGridFields(const std::string &t_name) 
   : EnumBase<GroundHeatTransfer_Slab_ManualGridFields>(t_name) {} 
  GroundHeatTransfer_Slab_ManualGridFields(int t_value) 
   : EnumBase<GroundHeatTransfer_Slab_ManualGridFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatTransfer_Slab_ManualGridFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatTransfer_Slab_ManualGridFields>::value()); }
   private:
    friend class EnumBase<GroundHeatTransfer_Slab_ManualGridFields>;
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
{ GroundHeatTransfer_Slab_ManualGridFields::NX_NumberofcellsintheXdirection, "NX_NumberofcellsintheXdirection", "NX: Number of cells in the X direction"},
{ GroundHeatTransfer_Slab_ManualGridFields::NY_NumberofcellsintheYdirection, "NY_NumberofcellsintheYdirection", "NY: Number of cells in the Y direction"},
{ GroundHeatTransfer_Slab_ManualGridFields::NZ_NumberofcellsintheZdirection, "NZ_NumberofcellsintheZdirection", "NZ: Number of cells in the Z direction"},
{ GroundHeatTransfer_Slab_ManualGridFields::IBOX_Xdirectioncellindicatorofslabedge, "IBOX_Xdirectioncellindicatorofslabedge", "IBOX: X direction cell indicator of slab edge"},
{ GroundHeatTransfer_Slab_ManualGridFields::JBOX_Ydirectioncellindicatorofslabedge, "JBOX_Ydirectioncellindicatorofslabedge", "JBOX: Y direction cell indicator of slab edge"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatTransfer_Slab_ManualGridFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatTransfer_Slab_ManualGridFields> OptionalGroundHeatTransfer_Slab_ManualGridFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_MANUALGRID_FIELDENUMS_HXX
