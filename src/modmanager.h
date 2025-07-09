#ifndef __MODMANAGER_H__
#define __MODMANAGER_H__

class ModManager {
public:
    static ModManager &get();
    bool init();

    /* Setters */
    const void setEnabled(bool v) { m_enabled = v; }

    const void setOffsetX(float v) { m_offsetX = v; }
    const void setOffsetY(float v) { m_offsetY = v; }
    const void setScale(float v) { m_scale = v; }
    void setOpacity(float v) { m_opacity = v; }

    /* Getters */
    bool getEnabled() const { return m_enabled; }

    float getOffsetX() const { return m_offsetX; }
    float getOffsetY() const { return m_offsetY; }
    float getScale() const { return m_scale; }
    float getOpacity() const { return m_opacity; }
protected:
    bool m_enabled = false;

    float m_offsetX = 0.f;
    float m_offsetY = 0.f;
    float m_scale = 0.f;
    float m_opacity = 0.f;

    inline static ModManager *s_instance = nullptr;
};

#endif /* __MODMANAGER_H__ */
