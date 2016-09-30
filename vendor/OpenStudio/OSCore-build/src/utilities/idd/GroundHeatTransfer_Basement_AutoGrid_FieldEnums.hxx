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

#ifndef UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_AUTOGRID_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_AUTOGRID_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatTransfer_Basement_AutoGridFields
 *  \brief Enumeration of GroundHeatTransfer:Basement:AutoGrid's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatTransfer_Basement_AutoGridFields, )
#else
class GroundHeatTransfer_Basement_AutoGridFields: public ::EnumBase<GroundHeatTransfer_Basement_AutoGridFields> {
 public: 
  enum domain 
  {
CLEARANCE_Distancefromoutsideofwalltoedge, SLABX_Xdimensionofthebuildingslab, SLABY_Ydimensionofthebuildingslab, ConcAGHeight_Heightofthefoundationwallabovegrade, SlabDepth_Thicknessofthefloorslab, BaseDepth_Depthofthebasementwallbelowgrade,   };
  GroundHeatTransfer_Basement_AutoGridFields()
   : EnumBase<GroundHeatTransfer_Basement_AutoGridFields>(CLEARANCE_Distancefromoutsideofwalltoedge) {} 
  GroundHeatTransfer_Basement_AutoGridFields(const std::string &t_name) 
   : EnumBase<GroundHeatTransfer_Basement_AutoGridFields>(t_name) {} 
  GroundHeatTransfer_Basement_AutoGridFields(int t_value) 
   : EnumBase<GroundHeatTransfer_Basement_AutoGridFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatTransfer_Basement_AutoGridFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatTransfer_Basement_AutoGridFields>::value()); }
   private:
    friend class EnumBase<GroundHeatTransfer_Basement_AutoGridFields>;
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
{ GroundHeatTransfer_Basement_AutoGridFields::CLEARANCE_Distancefromoutsideofwalltoedge, "CLEARANCE_Distancefromoutsideofwalltoedge", "CLEARANCE: Distance from outside of wall to edge"},
{ GroundHeatTransfer_Basement_AutoGridFields::SLABX_Xdimensionofthebuildingslab, "SLABX_Xdimensionofthebuildingslab", "SLABX: X dimension of the building slab"},
{ GroundHeatTransfer_Basement_AutoGridFields::SLABY_Ydimensionofthebuildingslab, "SLABY_Ydimensionofthebuildingslab", "SLABY: Y dimension of the building slab"},
{ GroundHeatTransfer_Basement_AutoGridFields::ConcAGHeight_Heightofthefoundationwallabovegrade, "ConcAGHeight_Heightofthefoundationwallabovegrade", "ConcAGHeight: Height of the foundation wall above grade"},
{ GroundHeatTransfer_Basement_AutoGridFields::SlabDepth_Thicknessofthefloorslab, "SlabDepth_Thicknessofthefloorslab", "SlabDepth: Thickness of the floor slab"},
{ GroundHeatTransfer_Basement_AutoGridFields::BaseDepth_Depthofthebasementwallbelowgrade, "BaseDepth_Depthofthebasementwallbelowgrade", "BaseDepth: Depth of the basement wall below grade"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatTransfer_Basement_AutoGridFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatTransfer_Basement_AutoGridFields> OptionalGroundHeatTransfer_Basement_AutoGridFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_AUTOGRID_FIELDENUMS_HXX
