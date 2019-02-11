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
	private:
		sf::Font u_font; /*!< Font par default */
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
		}
	};
}

#endif // RESSOURCESMANAGER_HPP
