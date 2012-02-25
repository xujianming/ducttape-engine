
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_COMPONENT_MUSICCOMPONENT
#define DUCTTAPE_ENGINE_COMPONENT_MUSICCOMPONENT

#include <Config.hpp>

#include <Scene/Component.hpp>

#include <QString>

#include <memory>

namespace dt {

/**
  * Plays a music file.
  */
class DUCTTAPE_API MusicComponent : public Component {
    Q_OBJECT
public:
    DT_SERIALIZABLE(MusicComponent)
    /**
     * Advanced constructor.
     * @param music_file_name The name of the music resource to play.
     * @param name The name for this component.
     * @see Component
     */
    MusicComponent(const QString& music_file_name = "", const QString& name = "");

    void OnCreate();
    void OnDestroy();
    void OnEnable();
    void OnDisable();
    void OnUpdate(double time_diff);
    void OnSerialize(IOPacket &packet);

    /**
      * Sets the file to load music from.
      * @param music_file_name The file to load the music from.
      */
    void SetMusicFileName(const QString& music_file_name);

    /**
      * Returns the file the music was loaded from.
      * @returns The file the music was loaded from.
      */
    const QString& GetMusicFileName() const;

public slots:
    /**
      * Sets the music volume.
      * @param volume The music volume. Minimum: 0. Maximum: 100. Default: 100.
      */
    void SetVolume(float volume);

    /**
      * Sets the global master sound/music volume.
      * @param volume The global master sound/music volume. Minimum: 0. Maximum: 100. Default: 100.
      */
    void SetMasterVolume(float volume);

    /**
      * Make the music start to fade.
      * @param time the fading duration time
      * @param target_volume the target volume
      */
    void Fade(double time, float target_volume);

    /**
      * Plays the music stream.
      * @see Component::Enable()
      */
    void PlayMusic();

    /**
      * Stops the music stream.
      */
    void StopMusic();

    /**
      * Stops the music stream. You can also use Component::Disable() to pause the music.
      * @see Component::Disable()
      */
    void PauseMusic();

signals:
    void VolumeChanged(float new_volume);
    void MasterVolumeChanged(float new_volume);
    void MusicPlayed();
    void MusicStopped();
    void MusicPaused();

private:
    /**
      * Private method. Prepares the music stream.
      */
    void _LoadMusic();

    QString mMusicFileName;     //!< The file the music was loaded from.
    bool mFadeFlag;             //!< The fading flag.
    double mElapsedTime;        //!< The elapsed time during the fading.
    double mFadeTime;           //!< The fading duration time.
    float mFadeVolume;          //!< The fading target volume.
};

}

#endif
