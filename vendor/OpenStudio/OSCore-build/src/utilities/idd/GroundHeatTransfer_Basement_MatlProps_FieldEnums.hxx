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

#ifndef UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_MATLPROPS_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_MATLPROPS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatTransfer_Basement_MatlPropsFields
 *  \brief Enumeration of GroundHeatTransfer:Basement:MatlProps's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatTransfer_Basement_MatlPropsFields, )
#else
class GroundHeatTransfer_Basement_MatlPropsFields: public ::EnumBase<GroundHeatTransfer_Basement_MatlPropsFields> {
 public: 
  enum domain 
  {
NMAT_Numberofmaterialsinthisdomain, DensityforFoundationWall, densityforFloorSlab, densityforCeiling, densityforSoil, densityforGravel, densityforWood, Specificheatforfoundationwall, Specificheatforfloorslab, Specificheatforceiling, Specificheatforsoil, Specificheatforgravel, Specificheatforwood, Thermalconductivityforfoundationwall, Thermalconductivityforfloorslab, Thermalconductivityforceiling, thermalconductivityforsoil, thermalconductivityforgravel, thermalconductivityforwood,   };
  GroundHeatTransfer_Basement_MatlPropsFields()
   : EnumBase<GroundHeatTransfer_Basement_MatlPropsFields>(NMAT_Numberofmaterialsinthisdomain) {} 
  GroundHeatTransfer_Basement_MatlPropsFields(const std::string &t_name) 
   : EnumBase<GroundHeatTransfer_Basement_MatlPropsFields>(t_name) {} 
  GroundHeatTransfer_Basement_MatlPropsFields(int t_value) 
   : EnumBase<GroundHeatTransfer_Basement_MatlPropsFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatTransfer_Basement_MatlPropsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatTransfer_Basement_MatlPropsFields>::value()); }
   private:
    friend class EnumBase<GroundHeatTransfer_Basement_MatlPropsFields>;
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
{ GroundHeatTransfer_Basement_MatlPropsFields::NMAT_Numberofmaterialsinthisdomain, "NMAT_Numberofmaterialsinthisdomain", "NMAT: Number of materials in this domain"},
{ GroundHeatTransfer_Basement_MatlPropsFields::DensityforFoundationWall, "DensityforFoundationWall", "Density for Foundation Wall"},
{ GroundHeatTransfer_Basement_MatlPropsFields::densityforFloorSlab, "densityforFloorSlab", "density for Floor Slab"},
{ GroundHeatTransfer_Basement_MatlPropsFields::densityforCeiling, "densityforCeiling", "density for Ceiling"},
{ GroundHeatTransfer_Basement_MatlPropsFields::densityforSoil, "densityforSoil", "density for Soil"},
{ GroundHeatTransfer_Basement_MatlPropsFields::densityforGravel, "densityforGravel", "density for Gravel"},
{ GroundHeatTransfer_Basement_MatlPropsFields::densityforWood, "densityforWood", "density for Wood"},
{ GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforfoundationwall, "Specificheatforfoundationwall", "Specific heat for foundation wall"},
{ GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforfloorslab, "Specificheatforfloorslab", "Specific heat for floor slab"},
{ GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforceiling, "Specificheatforceiling", "Specific heat for ceiling"},
{ GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforsoil, "Specificheatforsoil", "Specific heat for soil"},
{ GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforgravel, "Specificheatforgravel", "Specific heat for gravel"},
{ GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforwood, "Specificheatforwood", "Specific heat for wood"},
{ GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforfoundationwall, "Thermalconductivityforfoundationwall", "Thermal conductivity for foundation wall"},
{ GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforfloorslab, "Thermalconductivityforfloorslab", "Thermal conductivity for floor slab"},
{ GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforceiling, "Thermalconductivityforceiling", "Thermal conductivity for ceiling"},
{ GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforsoil, "thermalconductivityforsoil", "thermal conductivity for soil"},
{ GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforgravel, "thermalconductivityforgravel", "thermal conductivity for gravel"},
{ GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforwood, "thermalconductivityforwood", "thermal conductivity for wood"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatTransfer_Basement_MatlPropsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatTransfer_Basement_MatlPropsFields> OptionalGroundHeatTransfer_Basement_MatlPropsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_MATLPROPS_FIELDENUMS_HXX
