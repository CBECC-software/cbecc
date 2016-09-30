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

#ifndef UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_INSULATION_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_INSULATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatTransfer_Slab_InsulationFields
 *  \brief Enumeration of GroundHeatTransfer:Slab:Insulation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatTransfer_Slab_InsulationFields, )
#else
class GroundHeatTransfer_Slab_InsulationFields: public ::EnumBase<GroundHeatTransfer_Slab_InsulationFields> {
 public: 
  enum domain 
  {
RINS_Rvalueofunderslabinsulation, DINS_Widthofstripofunderslabinsulation, RVINS_Rvalueofverticalinsulation, ZVINS_Depthofverticalinsulation, IVINS_Flag_Isthereverticalinsulation,   };
  GroundHeatTransfer_Slab_InsulationFields()
   : EnumBase<GroundHeatTransfer_Slab_InsulationFields>(RINS_Rvalueofunderslabinsulation) {} 
  GroundHeatTransfer_Slab_InsulationFields(const std::string &t_name) 
   : EnumBase<GroundHeatTransfer_Slab_InsulationFields>(t_name) {} 
  GroundHeatTransfer_Slab_InsulationFields(int t_value) 
   : EnumBase<GroundHeatTransfer_Slab_InsulationFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatTransfer_Slab_InsulationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatTransfer_Slab_InsulationFields>::value()); }
   private:
    friend class EnumBase<GroundHeatTransfer_Slab_InsulationFields>;
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
{ GroundHeatTransfer_Slab_InsulationFields::RINS_Rvalueofunderslabinsulation, "RINS_Rvalueofunderslabinsulation", "RINS: R value of under slab insulation"},
{ GroundHeatTransfer_Slab_InsulationFields::DINS_Widthofstripofunderslabinsulation, "DINS_Widthofstripofunderslabinsulation", "DINS: Width of strip of under slab insulation"},
{ GroundHeatTransfer_Slab_InsulationFields::RVINS_Rvalueofverticalinsulation, "RVINS_Rvalueofverticalinsulation", "RVINS: R value of vertical insulation"},
{ GroundHeatTransfer_Slab_InsulationFields::ZVINS_Depthofverticalinsulation, "ZVINS_Depthofverticalinsulation", "ZVINS: Depth of vertical insulation"},
{ GroundHeatTransfer_Slab_InsulationFields::IVINS_Flag_Isthereverticalinsulation, "IVINS_Flag_Isthereverticalinsulation", "IVINS: Flag: Is there vertical insulation"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatTransfer_Slab_InsulationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatTransfer_Slab_InsulationFields> OptionalGroundHeatTransfer_Slab_InsulationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_INSULATION_FIELDENUMS_HXX
