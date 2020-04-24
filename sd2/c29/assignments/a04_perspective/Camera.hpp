enum eCameraClearBit 
{
   CAMERA_CLEAR_COLOR_BIT     = (1 << 0),       // A01
   CAMERA_CLEAR_DEPTH_BIT     = (1 << 1),       // A04
   CAMERA_CLEAR_STENCIL_BIT   = (1 << 2),       // A04
};
typedef uint eCameraClearFlags;


class Camera
{
   public:
      // be able to tell our system WHERE we're rendering to
      // if set to nullptr, will use default backbuffer
      void SetColorTarget( Texture* texture );           // A02
      void SetDepthStencilTarget( Texture* texture );    // A04
      
      void SetClearMode( eCameraClearFlags flags, rgba color, float depth = 0.0f, uint8_t stencil = 0 ); // A01, A04

      void SetPosition( Vec3 pos );                      // A04 
      void Translate( Vec3 pos );                        // A04
      void SetPitchRollYawRotation( float pitch, float roll, float yaw );  // A04

      void SetProjectionOrthographic( float size, float nearZ, float farZ );  // A03
      void SetProjectionPerspective( float fov, float nearZ, float farZ );    // A04

      // accessors
      Mat44 GetViewMatrix() const;           // A03, A04 
      Mat44 GetProjectionMatrix() const;     // A03

      // Helpers
      vec3 ClientToWorld( vec2 client, float ndcZ ); // A04
      vec3 WorldToClient( vec3 worldPos );           // A04

   public:
      Transform m_transform; 

      Texture* m_colorTarget = nullptr;         // A01
      Texture* m_depthStencilTarget = nullptr;  // A04

      eCameraClearFlags m_clearFlags   = 0;     // A01
      rgba m_clearColor                = WHITE; // A02
      float m_clearDepth               = 1.0f;  // A04
      float m_clearStencil             = 0;        // A04
};


// Creating the target?
void Game::Startup()
{
   m_gameCamera = new Camera(); 

   // option A
   m_gameCamera->SetColorTarget( nullptr ); // set default 
   m_gameCamera->CreateMatchingDepthStencilTarget();  // create a depth target that matches our current color target, 
                                                      // and set it as our color target

   // option B
   Texture2D* dsTex = Texture::CreateDepthStencil( outputDimensions ); 
   m_gameCamera->SetDepthSTencilTarget( dsTex );  // up to me to delete dsTex when program closes
} 