#if __cplusplus <= 199711L
	#error This library needs at least a C++11 compliant compiler
#endif

#ifndef RESSOURCESMANAGER_HPP
#define RESSOURCESMANAGER_HPP

/*!
 * \file RessourcesManager.hpp
 * \brief Gestionnaire de ressources
 * \author Aubin Detrez
 * \version 0.1
 */

#include <SFML/Graphics.hpp>
#include "Log.hpp"

/*! \namespace core
 * 
 * Regroupe les fonctions de base de l'application
 */
namespace core
{
	
	/*! \class RessourcesManager
	 * \brief Gestionnaire de ressources
	 *
	 *  La classe permet de stocker les ressources de l'application
	 * en évitant les doublons
	 */
	class RessourcesManager
	{
	public:
		/*!
		 *  \brief Acces au gestionnaire de ressources
		 *
		 *  Permet d'acceder au singleton
		 *
		 *  \return Pointeur vers l'instance du singleton accessible
		 * pendant toute l'execution du programme
		 */
		static RessourcesManager* getInstance()
		{
			static RessourcesManager instance; /*!< Instance statique */
			return &instance;
		}
		/*!
		 *  \brief Charge le font par default
		 *
		 *  \return true si bien chargé, false sinon
		 */
		bool loadDefaultFont();
		/*!
		 * \brief Recupere le font par default
		 *
		 * Ne pas oublier d'appeler core::RessourcesManager::loadDefaultFont
		 *
		 * \return le Font par default
		 */
		sf::Font* getDefaultFont()
		{
			return &u_font;
		}

		/*!
		 * \brief Charger la texture en mémoire
		 *
		 * \return False en cas d'erreur, true sinon
		 */
		bool loadTexture(const std::string& filename, unsigned int texName)
		{
			if (u_textures.count(texName) != 0) {
				LOG("Warning Texture %d is already loaded", texName);
				return false;
			}
			sf::Texture* tex = new sf::Texture();
			if (!tex->loadFromFile(filename)) {
				LOG("Error can't import texture file %s", filename.c_str());
				delete(tex);
				return false;
			}
			LOG("Ok Texture %d loaded", texName);
			tex->setSmooth(true);
			u_textures[texName] = tex;
			return true;
		}
		bool isTextureLoaded(unsigned int texName)
		{
			return u_textures.count(texName) != 0;
		}
		sf::Texture* getTexture(unsigned int texName)
		{
			if (isTextureLoaded(texName))
				return u_textures[texName];
			LOG("Error try to get non-existing texture %d", texName);
			return nullptr;
		}
	bool parseFile(const std::string& filename);
	private:
		sf::Font u_font; /*!< Font par default */
		std::map<unsigned int, sf::Texture*> u_textures; /*!< Textures charges */
		std::map<unsigned int, sf::IntRect> u_rects; /*!< Textures rects*/
		std::map<unsigned int, std::vector<sf::IntRect>> u_rects; /*!< Anim (texturesets) rects*/
		RessourcesManager()
		{
			#ifdef DEBUG
			LOG("Debug Create Ressource Manager");
			#endif // DEBUG
		}
		~RessourcesManager()
		{
			#ifdef DEBUG
			LOG("Debug Create Free Ressource Manager");
			#endif // DEBUG
			std::map<unsigned int, sf::Texture*>::iterator it;
			for(it=u_textures.begin(); it!=u_textures.end(); it++) {
				delete(it->second);
				LOG("Ok free texture %d", it->first);
			}
		}
	};
}

#endif // RESSOURCESMANAGER_HPP
