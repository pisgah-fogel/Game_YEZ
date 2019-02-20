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
		/*!
		 * \param texName id de la texture
		 * \return True si la texture est chargée, False sinon
		 */
		bool isTextureLoaded(unsigned int texName)
		{
			return u_textures.count(texName) != 0;
		}
		/*!
		 * \brief Accès à une texture chargée
		 *
		 * \param texName id de la texture
		 *
		 * \return un pointeur vers la texture, nullptr si la texture est
		 * introuvable (non chargée), le pointeur reste valable pendant tout
		 * l'execution du programme
		 */
		sf::Texture* getTexture(unsigned int texName)
		{
			if (isTextureLoaded(texName))
				return u_textures[texName];
			LOG("Error try to get non-existing texture %d", texName);
			return nullptr;
		}
		/*!
		 * \brief Accès à un rectangle de texture chargé
		 *
		 * \param id du rect (id_texture*100 + id_propre)
		 *
		 * \return un pointeur vers le rect, nullptr si
		 * introuvable (non chargée), le pointeur reste valable pendant tout
		 * l'execution du programme
		 */
		sf::IntRect* getRect(unsigned int id)
		{
			if (u_rects.count(id)>0) {
				return &u_rects[id];
			}
			LOG("Error try to get non-existing rect %d", id);
			return nullptr;
		}
		/*!
		 * \brief Accès à un ensemble de rectangles de texture chargé
		 *
		 * \param id du rect (id_texture*100 + id_propre)
		 *
		 * \return un pointeur vers l'ensemble, nullptr si
		 * introuvable (non chargée), le pointeur reste valable pendant tout
		 * l'execution du programme
		 */
		std::vector<sf::IntRect>* getRectSet(unsigned int id)
		{
			if (u_anims.count(id)>0) {
				return &u_anims[id];
			}
			LOG("Error try to get non-existing rect set %d", id);
			return nullptr;
		}
		/*!
		 * \brief Creer un sprite avec la texture et le rect
		 *
		 * \param texturerect id du rect (id_texture*100 + id_propre)
		 *
		 * \return un pointeur vers le sprite, nullptr si la texture ou le
		 * rect est introuvable (non chargée), le pointeur reste valable pendant
		 * toute l'execution du programme
		 */
		sf::Sprite* createSprite(unsigned int texturerect)
		{
			sf::IntRect* rect = getRect(texturerect);
			sf::Texture* tex = getTexture(texturerect/100);
			if (rect == nullptr || tex == nullptr)
				return nullptr;
			sf::Sprite* sp = new sf::Sprite();
			sp->setTexture(*tex);
			sp->setTextureRect(*rect);
			u_sprites.push_back(sp);
			return sp;
		}
		/*!
		 * \brief Parse le fichier
		 * \param filename nom du fichier
		 * \return True si aucun problème, False sinon
		 */
	bool parseFile(const std::string& filename);
	private:
		sf::Font u_font; /*!< Font par default */
		std::map<unsigned int, sf::Texture*> u_textures; /*!< Textures charges */
		std::map<unsigned int, sf::IntRect> u_rects; /*!< Textures rects*/
		std::map<unsigned int, std::vector<sf::IntRect>> u_anims; /*!< Anim (texturesets) rects */
		std::vector<sf::Sprite*> u_sprites; /*!< Sprites non annimés */
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
			std::vector<sf::Sprite*>::iterator it2;
			for(it2=u_sprites.begin(); it2 != u_sprites.end(); it2++) {
				delete(*it2);
				LOG("Ok free sprite");
			}
		}
	};
}

#endif // RESSOURCESMANAGER_HPP
