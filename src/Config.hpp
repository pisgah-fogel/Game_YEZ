#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <stdexcept>

#define DEFAULT_CONFIG "config.yez"

/*!
 * \file Config.hpp
 * \brief Gère les paramètres de l'application
 * \author Aubin Detrez
 * \version 0.1
 */

namespace utils
{
	/*! \class Config
	 * \brief Gère les paramètres de l'application
	 *
	 * Les paramètres peuvents venir d'un fichier  ou être definis dans le
	 * code, c'est un mode de communication interne déprécié mais
	 * qui fonctionne
	 */
	class Config
	{
	public:
		/*!
		 *  \brief Acces au gestionnaire de configurations
		 *
		 *  Permet d'acceder au singleton
		 *
		 *  \return Pointeur vers l'instance du singleton accessible
		 * pendant toute l'execution du programme
		 */
		static Config* getInstance()
		{
			static Config instance; /*!< Instance statique */
			return &instance;
		}
		/*!
		 *  \brief parse un fichier de paramètre et
		 * 	ajoute les paramètres lus a la classe
		 *
		 *  Le fichier dois être sous le format "YEZ"
		 *  créé pour notre propre usage
		 *
		 * \param filename chemin du fichier à parser
		 *
		 *  \return False en cas d'erreur, True sinon
		 */
		bool parseYEZ(const char* filename);
		/*!
		 *  \brief Cherche le paramètre
		 *
		 * Cherche si le paramètre existe (sous forme de chaine de caractère)
		 *
		 * \param str nom du paramètre
		 *
		 *  \return true si exist, false sinon
		 */
		bool stringExist(std::string str) {
			return u_string_map.count(str)>0;
		}
		/*!
		 *  \brief Cherche le paramètre entier
		 *
		 * Cherche si le paramètre existe (sous forme d'un entier)
		 *
		 * \param str nom du paramètre
		 *
		 *  \return true si exist, false sinon
		 */
		bool intExist(std::string str) {
			return u_int_map.count(str)>0;
		}
		/*!
		 *  \brief Cherche le paramètre float
		 *
		 * Cherche si le paramètre existe (sous forme d'un float)
		 *
		 * \param str nom du paramètre
		 *
		 *  \return true si exist, false sinon
		 */
		bool floatExist(std::string str) {
			return u_float_map.count(str)>0;
		}
		/*!
		 *  \brief Retourne le paramètre entier
		 *
		 * Si travailler avec la valeure qui est retournée dans
		 * le cas ou la paramètre n'existe pas pose un problème
		 * il est conseiller d'utiliser intExit() préalablement
		 *
		 * \param str nom du paramètre
		 *
		 *  \return La valeure du paramètre, 0 sinon
		 */
		int getInt(std::string str) {
			int a = 0;
			try {
				a = u_int_map[str];
			} catch (const std::out_of_range& oor) {
				LOG("Error No key %s", str);
			}
			return a;
		}
		/*!
		 *  \brief Retourne le paramètre float
		 *
		 * Si travailler avec la valeure qui est retournée dans
		 * le cas ou la paramètre n'existe pas pose un problème
		 * il est conseiller d'utiliser floatExit() préalablement
		 *
		 * \param str nom du paramètre
		 *
		 *  \return La valeure du paramètre, 0.f sinon
		 */
		float getFloat(std::string str) {
			float a = 0.f;
			try {
				a = u_float_map[str];
			} catch (const std::out_of_range& oor) {
				LOG("Error No key %s", str);
			}
			return a;
		}
		/*!
		 *  \brief Retourne le paramètre
		 *
		 * Si travailler avec la valeure qui est retournée dans
		 * le cas ou la paramètre n'existe pas pose un problème
		 * il est conseiller d'utiliser stringExit() préalablement
		 *
		 * \param str nom du paramètre
		 *
		 *  \return La valeure du paramètre, "" sinon
		 */
		std::string getString(std::string str) {
			std::string a = "";
			try {
				 a = u_string_map[str];
			} catch (const std::out_of_range& oor) {
				LOG("Error No key %s", str);
			}
			return a;
		}
		
	private:
		std::map<std::string, std::string> u_string_map; /*!< nom du parametre et valeure*/
		std::map<std::string, int> u_int_map; /*!< nom du parametre et valeure*/
		std::map<std::string, float> u_float_map; /*!< nom du parametre et valeure*/
		Config()
		{
			#ifdef DEBUG
			LOG("Debug Create Config Manager");
			#endif // DEBUG
			parseYEZ(DEFAULT_CONFIG);
		}
		~Config()
		{
			#ifdef DEBUG
			LOG("Debug Create Free Config Manager");
			#endif // DEBUG
		}
	};
}

#endif // CONFIG_HPP
