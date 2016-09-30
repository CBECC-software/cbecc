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

#ifndef UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_MATLPROPS_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_MATLPROPS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatTransfer_Slab_MatlPropsFields
 *  \brief Enumeration of GroundHeatTransfer:Slab:MatlProps's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatTransfer_Slab_MatlPropsFields, )
#else
class GroundHeatTransfer_Slab_MatlPropsFields: public ::EnumBase<GroundHeatTransfer_Slab_MatlPropsFields> {
 public: 
  enum domain 
  {
RHO_SlabMaterialdensity, RHO_SoilDensity, CP_SlabCP, CP_SoilCP, TCON_Slabk, TCON_Soilk,   };
  GroundHeatTransfer_Slab_MatlPropsFields()
   : EnumBase<GroundHeatTransfer_Slab_MatlPropsFields>(RHO_SlabMaterialdensity) {} 
  GroundHeatTransfer_Slab_MatlPropsFields(const std::string &t_name) 
   : EnumBase<GroundHeatTransfer_Slab_MatlPropsFields>(t_name) {} 
  GroundHeatTransfer_Slab_MatlPropsFields(int t_value) 
   : EnumBase<GroundHeatTransfer_Slab_MatlPropsFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatTransfer_Slab_MatlPropsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatTransfer_Slab_MatlPropsFields>::value()); }
   private:
    friend class EnumBase<GroundHeatTransfer_Slab_MatlPropsFields>;
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
{ GroundHeatTransfer_Slab_MatlPropsFields::RHO_SlabMaterialdensity, "RHO_SlabMaterialdensity", "RHO: Slab Material density"},
{ GroundHeatTransfer_Slab_MatlPropsFields::RHO_SoilDensity, "RHO_SoilDensity", "RHO: Soil Density"},
{ GroundHeatTransfer_Slab_MatlPropsFields::CP_SlabCP, "CP_SlabCP", "CP: Slab CP"},
{ GroundHeatTransfer_Slab_MatlPropsFields::CP_SoilCP, "CP_SoilCP", "CP: Soil CP"},
{ GroundHeatTransfer_Slab_MatlPropsFields::TCON_Slabk, "TCON_Slabk", "TCON: Slab k"},
{ GroundHeatTransfer_Slab_MatlPropsFields::TCON_Soilk, "TCON_Soilk", "TCON: Soil k"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatTransfer_Slab_MatlPropsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatTransfer_Slab_MatlPropsFields> OptionalGroundHeatTransfer_Slab_MatlPropsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATTRANSFER_SLAB_MATLPROPS_FIELDENUMS_HXX
